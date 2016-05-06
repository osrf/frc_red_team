#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export GAZEBO_MODEL_PATH=${DIR}/frcred_gazebo/models:${GAZEBO_MODEL_PATH}
