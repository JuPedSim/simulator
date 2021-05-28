import pytest
from jupedsim.util.simulation_files import SimulationFiles
import pathlib


def test_all_required_simulation_files_found(tmp_path: pathlib.Path):
    world_dxf = tmp_path / "world.dxf"
    world_dxf.write_text("Test")
    sim_files = SimulationFiles(tmp_path)


def test_world_dxf_not_exists(tmp_path: pathlib.Path):
    with pytest.raises(FileNotFoundError):
        sim_files = SimulationFiles(tmp_path)
