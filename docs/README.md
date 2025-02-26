# live-view
shhhhhhhhhhh

## Building via Docker
### MacOS
* docker build --platform linux/amd64 -t live-view .
* docker run --platform linux/amd64 -p 8080:8080 live-view:latest
* but we will use the docker-compose.yml -> docker compose up --build or without build --parallel

## Building via CMake
* download the vcpkg ports in the vcpkg.json
* clone the repo
* mkdir build in the base project dir
* cd build && cmake .. && make
* start the postgres server (if Mac->brew services start postgresql@15)
* ./src/app
* configure postgres service and pg-admin locally - using the same variables -> in .env, see .env.example
* ctest -R <test_name>
* ./test_name --gtest_filter=Test.TestName

## Building For Xcode
* in build dir -> cmake -G Xcode ..