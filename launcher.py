

# Launches the executable.
# Todo: Add hot reloading whenever the exe is replaced (aka, project is recompiled).
# Also todo: make this function use command line arguments to initialize the
# cpp bot.

import os
from rlbot.agents.base_agent import BaseAgent

class CppBot(BaseAgent):
  
  def __init__(self, name, team, index):
    super().__init__(name, team, index)
    
    print("Initializing c++ framework")

    old_wd = os.getcwd()

    abspath = os.path.abspath(__file__)
    dname = os.path.dirname(abspath)
    os.chdir(dname)

    # Generate command to launch bot.
    os.system("bot.exe -t " + str(team) + " -i " + str(index) + " -n \"" + name + "\"")
    os.chdir(old_wd)

if __name__ == "__main__":
  from rlbot_gui import gui;
  gui.start()

