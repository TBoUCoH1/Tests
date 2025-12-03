### Для C++:
1. cmake -S . -B build
2. cmake --build build
3. ./build/run_tests
4. ./build/run_bench
5. lcov --capture --directory build --output-file coverage.info --ignore-errors mismatch,gcov,empty && lcov --remove coverage.info '/usr/*' '*/build/_deps/*' -o coverage.info --ignore-errors empty,unused && genhtml coverage.info --output-directory coverage_report --ignore-errors empty

### Для Go:
1. go build ./...
2. go build -o app.exe .
3. go test ./structures -coverprofile=coverage.out
4. go tool cover -html=coverage.out -o coverage.html
5. go test ./structures -coverprofile=coverage.out; go tool cover -html=coverage.out -o coverage.html
