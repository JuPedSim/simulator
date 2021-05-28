import errno
import os
import pathlib


def require_file_exists(f: pathlib.Path) -> None:
    """
    Checks the specified paths exists.

    Will throw if the file does not exist.
    Use this for required files only.
    """
    if not f.exists():
        raise FileNotFoundError(errno.ENOENT, os.strerror(errno.ENOENT), f)


class SimulationFiles:
    def __init__(self, path: pathlib.Path) -> None:
        self.world_dxf = path / "world.dxf"
        self.events_json = path / "events.json"
        self._check_all_files_exist()

    def _check_all_files_exist(self) -> None:
        require_file_exists(self.world_dxf)
        require_file_exists(self.events_json)
