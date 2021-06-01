import pathlib

from jupedsim.util.file_operations import require_file_exists


class SimulationFiles:
    def __init__(self, path: pathlib.Path) -> None:
        self.world_dxf = path / "world.dxf"
        self.events_json = path / "events.json"
        self._check_all_files_exist()

    def _check_all_files_exist(self) -> None:
        require_file_exists(self.world_dxf)
        require_file_exists(self.events_json)
