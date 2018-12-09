#!/bin/bash
echo "Make sure the robot base has power ('Clean' is illuminated green)"
echo "Press enter when ready"
read
echo "Starting Xplorer"

gnome-terminal --tab -e "bash xplorer_ws/src/user_interface/scripts/roscore.bash" --tab -e "bash -c 'sleep 2 && bash xplorer_ws/src/user_interface/scripts/launch_hw_interface.bash'" --tab -e "bash -c 'sleep 2 && bash xplorer_ws/src/user_interface/scripts/launch_navigation.bash'" --tab -e "bash -c 'sleep 2 && bash xplorer_ws/src/user_interface/scripts/launch_mapping.bash'" --tab -e "bash -c 'sleep 2 && bash xplorer_ws/src/user_interface/scripts/launch_execution.bash'" --tab -e "bash -c 'sleep 2 && bash xplorer_ws/src/user_interface/scripts/launch_ui.bash'" --tab -e "bash -c 'sleep 7 && bash xplorer_ws/src/user_interface/scripts/launch_load_params.bash'"

echo "Run the command 'stop_robot' to stop robot"
