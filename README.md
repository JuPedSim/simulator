# Simulator

## Developing

Main development platform is Linux although we aim to provide MacOS and Windows
binaries as well. Of the many Linux distributions we aim to support Ubuntu 20.04
primarily but every distribution should work where you have access to the
required dependencies.

### Dependencies

To build you will need the following system dependencies installed:

* Python 3.8 binaries

* Python 3.8 headers

* clang-format-10

* clang-tidy-10

* parallel

* wget

* gcc or clang (c++17 support is required)

Additionally you will need a few python packages. It is recommended to install all
dependencies listed in `requirements.txt` into a virtual environment, e.g.:

```bash
python -m venv ~/simulator-venv
source ~/simulator-venv/bin/activate
pip install -r requirements.txt
```

Once system and python dependencies are installed you will need to build
third-party dependencies with `cpp/scripts/setup-dependencies.sh`, e.g.:

```bash
./cpp/scripts/setup-dependencies.sh ~/simulator-deps
```

The above call will download several third-party libraries, compile them and
install them into `~/simulator-deps` (or any other location you specified)

### Building C++ libraries

Do the 'cmake-dance' and create a build folder, configure the project and build
the sources:

```bash
mkdir ~/simulator-build
cd ~/simulator-build
cmake -DCMAKE_PREFIX_PATH=~/simulator-deps -DCMAKE_BUILD_TYPE=Debug <path-to-repository>/cpp
cmake --build . -j
```

The command above assumes that the third party dependencies that you build with
`setup-dependencies.sh` have been installed into `~/simulator-deps`. If you
selected a different location, make sure to substitute the location in the above
call.

### Running tests

To run all tests at once call `ctest -j$(nproc)` in the build folder.

### Running jps

To run *jps* the location of the jpscore library (e.g., on Linux `jpscore.so`) needs to be in the `PYTHONPATH`, e.g.:

```bash
PYTHONPATH=~/simulation-build/bin ./jps/jps --help
```
### Repository Layout

The repository layout follows the high level architecture of the *jps* tool. At
the core is a C++ library for pedestrian simulation. This core is wrapped
with `pybind11` to allow use of the simulation library from python. Lastly there
is the actual *jps* application written in python. The python layer is used to
handle all the non-resource / compute intensive parts of the application, i.e.
initial setup, file handling etc.

```
+----------------+
|      jps       | -> jps/
+----------------+
+----------------+
| Python wrapper | -> cpp/pycore/
+----------------+
+----------------+
|   Simulation   | -> cpp/libcore/
+----------------+
```
The above separation can be seen in the folder structure as well:

```
.
├── container     <= dockerfile for CI environment
├── cpp           <= hosts the main CMakeLists.txt
│   ├── cmake
│   ├── libcore   <= core library
│   │   ├── source
│   │   └── test
│   ├── pycore    <= python binding
│   │   ├── source
│   │   └── test
│   └── scripts   <= support scripts, e.g. dependency download, compilie & isntall
├── jps
│   ├── jps       <= *jps* entry point
│   └── jupedsim  <= remaining python code
└── scripts       <= scripts used in devlopment / CI
```
