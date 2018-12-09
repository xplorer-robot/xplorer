
#!/bin/bash

rosrun dynamic_reconfigure dynparam load /move_base_node ~/xplorer_ws/src/execution/params/move_base_node.yaml -t 5
rosrun dynamic_reconfigure dynparam load /move_base_node/global_costmap ~/xplorer_ws/src/execution/params/global.yaml -t 5
rosrun dynamic_reconfigure dynparam load /move_base_node/global_costmap/inflation_layer ~/xplorer_ws/src/execution/params/global_in.yaml
rosrun dynamic_reconfigure dynparam load /move_base_node/global_costmap/obstacle_layer ~/xplorer_ws/src/execution/params/global_ob.yaml
rosrun dynamic_reconfigure dynparam load /move_base_node/local_costmap/inflation_layer ~/xplorer_ws/src/execution/params/local_in.yaml
rosrun dynamic_reconfigure dynparam load /move_base_node/local_costmap/obstacle_layer ~/xplorer_ws/src/execution/params/local_ob.yaml

