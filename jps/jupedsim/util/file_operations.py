import errno
import os
import pathlib
from pathlib import Path


def require_file_exists(f: pathlib.Path) -> None:
    """
    Checks the specified paths exists.

    Will throw if the file does not exist.
    Use this for required files only.
    """
    if not f.exists():
        raise_file_not_found_error(f)


def raise_file_not_found_error(path: Path):
    raise FileNotFoundError(errno.ENOENT, os.strerror(errno.ENOENT), str(path))
