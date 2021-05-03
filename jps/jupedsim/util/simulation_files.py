import errno
import os
import pathlib


class SimulationFiles:
    def __init__(self, path: pathlib.Path) -> None:
        self.world_dxf = path / "world.dxf"
        if not self.world_dxf.exists():
            raise FileNotFoundError(
                errno.ENOENT, os.strerror(errno.ENOENT), self.world_dxf
            )
