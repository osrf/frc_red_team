red()
{ 
    local server_ip=${1:-172.23.1.30}

    set -e
    . /opt/ros/jade/setup.bash
    . ${HOME}/frc_ws/install/setup.bash
    . ${HOME}/frc_ws/install/share/frc2016_competition/setup.sh 
    export ROS_MASTER_URI=http://${server_ip}:11311
    set +e
}
