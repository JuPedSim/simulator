# Utility scripts for development

## check-format-cpp / check-format-py

These two scripts are intended to be used by the CI to validate that all sources are formated
according to the projects formating rules. In case of C and C++ see `.clang-format`. For Python we
are relying on black and isort, see pyproject.toml for black and isort settings.

## format-cpp / format-py

In case you have difficulties configuring your ide of choice to auto reformat code you can use these
scripts to reformat your cpp and python code respectively.
