#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace rlbot {

const float BALL_PRED_SLICES_PER_SEC = 60.0;
const float BALL_PREDICTION_DELTA = 1.0 / BALL_PRED_SLICES_PER_SEC;

const short MAX_CARS = 64;

const int CONTROLLER_OUTPUT_SIZE = 64;

// Number of seconds before connection is considered to be lost.
const int CONNECTION_TIMEOUT = 30;

const std::string ARG_NAME = "-n";
const std::string ARG_TEAM = "-t";
const std::string ARG_INDEX = "-i";

}

#endif