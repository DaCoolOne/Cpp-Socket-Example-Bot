// Deals with reading and writing packet data from rlbot.

#include <string>
#include <iostream>
#include <ctime>
#include "networking/socket_lib.h"

#include "Agent.h"
#include "structs/DynamicBuffer.h"
#include "flatbuffers/rlbot_generated.h"
#include "structs/enums.h"
#include "structs/GameTickPacket.h"
#include "structs/FieldInfo.h"
#include "structs/Controller.h"

// Todo: get rid of this.
#define PORT 23234

// Feast your eyes on the messiest code I have written in a long time.
namespace rlbot {

using namespace networking;

int main(int argc, char *argv[])
{
  std::string agent_name = "UNKNOWN";
  short agent_team_index = -1;
  short agent_bot_index = -1;
  
  // Read command line args for bot meta-data
  std::string cur_arg;
  std::string prev_arg = "";
  for(short i = 0; i < argc; i ++)
  {
    cur_arg = argv[i];

    if(prev_arg == ARG_TEAM)
    {
      agent_team_index = stoi(cur_arg);
    }
    else if(prev_arg == ARG_INDEX)
    {
      agent_bot_index = stoi(cur_arg);
    }
    else if(prev_arg == ARG_NAME)
    {
      agent_name = cur_arg;
    }
    
    prev_arg = cur_arg;
  }

  if(agent_team_index < 0 || agent_bot_index < 0)
  {
    std::cerr << "Error initializing c++ framework, too few command line arguments" << std::endl;
    return -1;
  }

  std::cout << "Cpp ALPHA Initializing" << std::endl;

  // const int AGENT_INDEX = 

  // Packet meta-data
  uint16_t packet_type;
  uint16_t packet_size;

  unsigned char header_buffer[4];

  // Buffers. Mostly this class deals with memory mangement.
  DynamicBuffer<char> game_packet_buf;
  DynamicBuffer<char> field_info_buf;
  DynamicBuffer<char> match_settings_buf;
  DynamicBuffer<char> ball_prediction_buf;

  DynamicBuffer<char> player_input_buf;

  DynamicBuffer<char> default_buf;

  GameTickPacket packet;
  ControllerState controller_output;

  const flat::MatchSettings * match_settings = nullptr;
  FieldInfo field_info;

  SOCKET rlbot_socket;

  if(!InitSocket(rlbot_socket))
    return -1;

  if(!AttemptConnect(rlbot_socket, PORT))
    return -1;
  
  std::cout << "Connection established." << std::endl;

  bool is_running = true;

  time_t last_data_packet_recieved = time(NULL);

  RECIEVE_FLAGS recieve_flag = RECIEVE_FLAGS::NONE;

  SOCKET * sock_ptr = &rlbot_socket;
  Agent bot_agent(agent_name, agent_team_index, agent_bot_index, sock_ptr); //, &rlbot_socket);

  int recv_status;
  
  // Connection loop.
  while(is_running)
  {
    MakeNonBlocking(rlbot_socket);
    recv_status = recv(rlbot_socket, reinterpret_cast<char*>(header_buffer), 2, 0);

    while(recv_status > 0)
    {
      MakeBlocking(rlbot_socket);
      last_data_packet_recieved = time(NULL);
      
      packet_type = (static_cast<uint16_t>(header_buffer[0]) << 8) | static_cast<uint16_t>(header_buffer[1]);

      recv(rlbot_socket, reinterpret_cast<char*>(header_buffer), 2, 0);
      packet_size = (static_cast<uint16_t>(header_buffer[0]) << 8) | static_cast<uint16_t>(header_buffer[1]);

      // Select which buffer to use. Keeps us from having to constantly resize the
      //  buffer.
      if(packet_type == RECIEVE_PACKET::GAME_PACKET)
      {
        game_packet_buf.resize(packet_size);

        recv(rlbot_socket, game_packet_buf.get(), packet_size, 0);

        recieve_flag = recieve_flag | RECIEVE_FLAGS::GAME_PACKET;
      }
      else if(packet_type == RECIEVE_PACKET::FIELD_INFO)
      {
        field_info_buf.resize(packet_size);

        recv(rlbot_socket, field_info_buf.get(), packet_size, 0);

        recieve_flag = recieve_flag | RECIEVE_FLAGS::FIELD_INFO;
      }
      else if(packet_type == RECIEVE_PACKET::MATCH_SETTINGS)
      {
        match_settings_buf.resize(packet_size);

        recv(rlbot_socket, match_settings_buf.get(), packet_size, 0);

        recieve_flag = recieve_flag | RECIEVE_FLAGS::MATCH_SETTINGS;
      }
      else if(packet_type == RECIEVE_PACKET::BALL_PREDICTION)
      {
        ball_prediction_buf.resize(packet_size);

        recv(rlbot_socket, ball_prediction_buf.get(), packet_size, 0);

        recieve_flag = recieve_flag | RECIEVE_FLAGS::BALL_PREDICTION;
      }
      else
      {
        // Only allow default buffer to grow in size.
        default_buf.upscale(packet_size);
        recv(rlbot_socket, default_buf.get(), packet_size, 0);
      }
      
      MakeNonBlocking(rlbot_socket);
      recv_status = recv(rlbot_socket, reinterpret_cast<char*>(header_buffer), 2, 0);
    }

    // Ball prediction
    // Todo: Create compiler flag that disable ball prediction.
    if((recieve_flag & RECIEVE_FLAGS::BALL_PREDICTION) != RECIEVE_FLAGS::NONE)
    {
      auto data = flatbuffers::GetRoot<flat::BallPrediction>(ball_prediction_buf.get());

      bot_agent.updateBallPrediction(data);

      recieve_flag = recieve_flag ^ RECIEVE_FLAGS::BALL_PREDICTION;
    }

    if((recieve_flag & RECIEVE_FLAGS::GAME_PACKET) != RECIEVE_FLAGS::NONE)
    {
      MakeNonBlocking(rlbot_socket);

      auto data = flatbuffers::GetRoot<flat::GameTickPacket>(game_packet_buf.get());
      packet.update(data);
      field_info.updateTick(data);

      // Agent execution
      controller_output = bot_agent.process(packet);

      // Generator controller state.
      flatbuffers::FlatBufferBuilder builder(CONTROLLER_OUTPUT_SIZE);

      // Todo: Actually link this to the serialize function of controller_output
      auto controller_state_offset = controller_output.serialize(builder);
      
      auto player_input_offset = flat::CreatePlayerInput(builder, bot_agent.getBotIndex(), controller_state_offset);

      builder.Finish(player_input_offset);

      uint16_t size = builder.GetSize();

      MakeHeader(header_buffer, SEND_PACKET::PLAYER_INPUT, size);

      // Send the resulting controller state.
      int result = send(rlbot_socket, reinterpret_cast<char*>(header_buffer), 4, 0);
      result = send(rlbot_socket, reinterpret_cast<char*>(builder.GetBufferPointer()), size, 0);

      recieve_flag = recieve_flag ^ RECIEVE_FLAGS::GAME_PACKET;
    }
    
    // Match settings
    if((recieve_flag & RECIEVE_FLAGS::MATCH_SETTINGS) != RECIEVE_FLAGS::NONE)
    {
      match_settings = flatbuffers::GetRoot<flat::MatchSettings>(match_settings_buf.get());
      
      recieve_flag = recieve_flag ^ RECIEVE_FLAGS::BALL_PREDICTION;
    }

    if((recieve_flag & RECIEVE_FLAGS::FIELD_INFO) != RECIEVE_FLAGS::NONE)
    {
      auto flat_field_info = flatbuffers::GetRoot<flat::FieldInfo>(field_info_buf.get());

      field_info.update(flat_field_info);

      recieve_flag = recieve_flag ^ RECIEVE_FLAGS::FIELD_INFO;
    }

    if(time(NULL) - last_data_packet_recieved > CONNECTION_TIMEOUT)
      is_running = false;
    else if(recv_status == 0)
      is_running = false;
  }

  std::cout << "Connection lost / stale. Shutting down." << std::endl;

  return 0;
}

} // namespace rlbot

int main(int argc, char *argv[])
{
  return rlbot::main(argc, argv);
}
