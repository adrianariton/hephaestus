# OpenMP Environment setup

See [forker_test.cpp](forker_test.cpp) for more info. This is created for testing parralelization for HEPHAESTUS++. Soon the code will be reorganized.

To run:

```
g++-11 -fopenmp forker_test.cpp -o forker
./forker
```

## Errs

### ARM
If `<omp.h>` not found on macos, run
```bash
ln -s /opt/homebrew/Cellar/libomp/16.0.0/include/omp.h omp.h
```
from the base folder of the project.

### Other architectures: to be documented