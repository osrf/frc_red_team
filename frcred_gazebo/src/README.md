# Build

mkdir build
cd build
cmake ..
make

# Add to path

Something like this:

~~~
export GAZEBO_PLUGIN_PATH=`pwd`:/usr/local/lib/x86_64-linux-gnu/gazebo-8/plugins/:$GAZEBO_PLUGIN_PATH
~~~

We need to add the default Gazebo plugin path otherwise the DiffDrive plugin doesn't work.


# Keyboard teleop

For now, use keyboard teleop as Gazebo GUI plugin, adding it to `gui.ini`:

~~~
[overlay_plugins]
filenames=libteleop.so
~~~

