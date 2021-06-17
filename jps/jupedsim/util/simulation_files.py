import pathlib

from jupedsim.util.file_operations import require_file_exists
from jupedsim.util.loghelper import log_info


class SimulationFiles:
    def __init__(self, path: pathlib.Path) -> None:
        self.world_dxf = path / "world.dxf"
        self.events_json = path / "events.json"
        self._check_all_files_exist()
        self.trajctory_out = path / "trajectory.txt"
        self._check_for_existing_traj()

    def _check_all_files_exist(self) -> None:
        require_file_exists(self.world_dxf)
        require_file_exists(self.events_json)

    def _check_for_existing_traj(self) -> None:
        if self.trajctory_out.exists():
            log_info("Trajectory file already exists, it will be overwritten.")
