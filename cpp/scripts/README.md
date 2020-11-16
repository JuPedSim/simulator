# setup-dependencies.sh

Use this script to download and install all native dependencies for C++ develeopment dependencies
into an install tree.

Usage is:

```bash
./setup-dependencies.sh <path-to-install-to>
```

Alternatively the install path can be omitted, in this case the installation will be done into
`/usr/local`

Currently the following dependencies are installed:

* Googletest 1.10.0 [https://github.com/google/googletest]

* Pybind11 2.5.0 [https://github.com/pybind/pybind11]

* Fmt 7.1.2 [https://github.com/fmtlib/fmt]
