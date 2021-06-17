import logging
import pathlib

import pytest
from jupedsim.util.simulation_files import SimulationFiles


def test_all_required_simulation_files_found(tmp_path: pathlib.Path):
    world_dxf = tmp_path / "world.dxf"
    world_dxf.write_text("Test")
    events_json = tmp_path / "events.json"
    events_json.write_text("Test")
    sim_files = SimulationFiles(tmp_path)


def test_missing_world_dxf_is_an_error(tmp_path: pathlib.Path):
    events_json = tmp_path / "events.json"
    events_json.write_text("Test")
    with pytest.raises(FileNotFoundError):
        sim_files = SimulationFiles(tmp_path)


def test_missing_events_json_is_an_error(tmp_path: pathlib.Path):
    world_dxf = tmp_path / "world.dxf"
    world_dxf.write_text("Test")
    with pytest.raises(FileNotFoundError):
        sim_files = SimulationFiles(tmp_path)


def test_existing_trajectory_file_gives_log_message(
    tmp_path: pathlib.Path, caplog
):
    caplog.set_level(logging.INFO)

    world_dxf = tmp_path / "world.dxf"
    world_dxf.write_text("Test")
    events_json = tmp_path / "events.json"
    events_json.write_text("Test")
    trajectory_txt = tmp_path / "trajectory.txt"
    trajectory_txt.write_text("Test")

    sim_files = SimulationFiles(tmp_path)
    assert (
        "Trajectory file already exists, it will be overwritten."
        in caplog.text
    )
