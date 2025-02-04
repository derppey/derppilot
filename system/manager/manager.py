#!/usr/bin/env python3
import datetime
import os
import signal
import sys
import traceback

from cereal import log, custom
import cereal.messaging as messaging
import openpilot.system.sentry as sentry
from openpilot.common.params import Params, ParamKeyType
from openpilot.common.text_window import TextWindow
from openpilot.system.hardware import HARDWARE
from openpilot.system.manager.helpers import unblock_stdout, write_onroad_params, save_bootlog
from openpilot.system.manager.process import ensure_running
from openpilot.system.manager.process_config import managed_processes
from openpilot.system.athena.registration import register, UNREGISTERED_DONGLE_ID
from openpilot.common.swaglog import cloudlog, add_file_handler
from openpilot.system.version import get_build_metadata, terms_version, training_version
from openpilot.system.hardware.hw import Paths


def manager_init() -> None:
  save_bootlog()

  build_metadata = get_build_metadata()

  params = Params()
  params.clear_all(ParamKeyType.CLEAR_ON_MANAGER_START)
  params.clear_all(ParamKeyType.CLEAR_ON_ONROAD_TRANSITION)
  params.clear_all(ParamKeyType.CLEAR_ON_OFFROAD_TRANSITION)
  if build_metadata.release_channel:
    params.clear_all(ParamKeyType.DEVELOPMENT_ONLY)

  default_params: list[tuple[str, str | bytes]] = [
    ("CompletedTrainingVersion", "0"),
    ("DisengageOnAccelerator", "0"),
    ("GsmMetered", "1"),
    ("HasAcceptedTerms", "0"),
    ("LanguageSetting", "main_en"),
    ("OpenpilotEnabledToggle", "1"),
    ("LongitudinalPersonality", str(log.LongitudinalPersonality.standard)),
  ]

  chubbs_default_params: list[tuple[str, str | bytes]] = [
    ("DynamicExperimentalControl", "0"),
    ("Mads", "1"),
    ("MadsMainCruiseAllowed", "1"),
    ("MadsPauseLateralOnBrake", "0"),
    ("MadsUnifiedEngagementMode", "1"),
    ("ModelManager_LastSyncTime", "0"),
    ("ModelManager_ModelsCache", ""),
    ("AccelerationPath", "0"),
    ("AccelerationProfile", "0"),
    ("AdjacentLeadsUI", "0"),
    ("AdjacentPath", "0"),
    ("AdjacentPathMetrics", "0"),
    ("AdvancedCustomUI", "0"),
    ("AdvancedLateralTune", "0"),
    ("AggressiveFollow", "0"),
    ("AggressiveJerkAcceleration", "0"),
    ("AggressiveJerkDanger", "0"),
    ("AggressiveJerkDeceleration", "0"),
    ("AggressiveJerkSpeed", "0"),
    ("AggressiveJerkSpeedDecrease", "0"),
    ("AggressivePersonalityProfile", "0"),
    ("AlertVolumeControl", "0"),
    ("BigMap", "0"),
    ("BlindSpotMetrics", "0"),
    ("BlindSpotPath", "0"),
    ("BorderMetrics", "0"),
    ("BrakeSignal", "0"),
    ("CustomAlerts", "0"),
    ("CustomColors", "0"),
    ("CustomCruise", "0"),
    ("CustomCruiseLong", "0"),
    ("CustomDistanceIcons", "0"),
    ("CustomIcons", "0"),
    ("CustomPersonalities", "0"),
    ("CustomSignals", "0"),
    ("CustomSounds", "0"),
    ("CustomUI", "0"),
    ("DriverCamera", "0"),
    ("ForceStandstill", "0"),
    ("ForceStops", "0"),
    ("HKGtuning", "0"),
    ("HatTrick", "0"),
    ("IncreasedStoppedDistance", "0"),
    ("JerkInfo", "0"),
    ("LaneChangeCustomizations", "0"),
    ("LaneChangeTime", "0"),
    ("LaneDetectionWidth", "0"),
    ("LaneLinesWidth", "0"),
    ("LeadDepartingAlert", "0"),
    ("LeadDetectionThreshold", "0"),
    ("LeadInfo", "0"),
    ("LongitudinalMetrics", "0"),
    ("LongitudinalTune", "0"),
    ("LongPitch", "0"),
    ("MTSCCurvatureCheck", "0"),
    ("MTSCEnabled", "0"),
    ("NavigationUI", "0"),
    ("NNFF", "0"),
    ("NNFFLite", "0"),
    ("NoLogging", "0"),
    ("NoUploads", "0"),
    ("NudgelessLaneChange", "0"),
    ("OneLaneChange", "0"),
    ("OnroadDistanceButton", "0"),
    ("PathEdgeWidth", "0"),
    ("PathWidth", "0"),
    ("PersonalizeOpenpilot", "0"),
    ("QOLLateral", "0"),
    ("QOLLongitudinal", "0"),
    ("QOLVisuals", "0"),
    ("RainbowPath", "0"),
    ("RefuseVolume", "0"),
    ("RelaxedFollow", "0"),
    ("RelaxedJerkAcceleration", "0"),
    ("RelaxedJerkDanger", "0"),
    ("RelaxedJerkDeceleration", "0"),
    ("RelaxedJerkSpeed", "0"),
    ("RelaxedJerkSpeedDecrease", "0"),
    ("RelaxedPersonalityProfile", "0"),
    ("ReverseCruise", "0"),
    ("RoadEdgesWidth", "0"),
    ("RoadNameUI", "0"),
    ("RotatingWheel", "0"),
    ("ScreenBrightness", "0"),
    ("ScreenBrightnessOnroad", "0"),
    ("ScreenManagement", "0"),
    ("ScreenRecorder", "0"),
    ("ScreenTimeout", "0"),
    ("ScreenTimeoutOnroad", "0"),
    ("ShowSteering", "0"),
    ("ShowStoppingPoint", "0"),
    ("ShowStoppingPointMetrics", "0"),
    ("Sidebar", "0"),
    ("SidebarMetrics", "0"),
    ("SignalMetrics", "0"),
    ("SLCConfirmation", "0"),
    ("SLCConfirmationHigher", "0"),
    ("SLCConfirmationLower", "0"),
    ("SLCLookaheadHigher", "0"),
    ("SLCLookaheadLower", "0"),
    ("SLCFallback", "0"),
    ("SLCOverride", "0"),
    ("SLCPriority1", "0"),
    ("SLCPriority2", "0"),
    ("SLCPriority3", "0"),
    ("SpeedLimitChangedAlert", "0"),
    ("SpeedLimitController", "0"),
    ("StandardFollow", "0"),
    ("StandardJerkAcceleration", "0"),
    ("StandardJerkDanger", "0"),
    ("StandardJerkDeceleration", "0"),
    ("StandardJerkSpeed", "0"),
    ("StandardJerkSpeedDecrease", "0"),
    ("StandardPersonalityProfile", "0"),
    ("StandbyMode", "0"),
    ("StoppedTimer", "0"),
    ("TacoTune", "0"),
    ("TetheringEnabled", "0"),
    ("TuningInfo", "0"),
    ("TuningLevel", "0"),
    ("TurnAggressiveness", "0"),
    ("TurnDesires", "0"),
    ("VisionTurnControl", "0"),
    ("WarningImmediateVolume", "0"),
    ("WarningSoftVolume", "0"),
    ("WheelIcon", "0"),
    ("WheelSpeed", "0"),
    ("DECCurves", "0"), 
    ("DECCurvesLead", "0"),
    ("DECLead", "0"),
    ("DECModelStopTime", "0"),
    ("DECNavigation", "0"), 
    ("DECNavigationIntersections", "0"),
    ("DECNavigationLead", "0"),
    ("DECNavigationTurns", "0"),
    ("DECSignalSpeed", "0"),
    ("DECSignalLaneDetection", "0"),
    ("DECSlowerLead", "0"),
    ("DECSpeed", "0"),
    ("DECSpeedLead", "0"),
    ("DECStoppedLead", "0"),
    ("ShowDECStatus", "0"),
    ("HyundaiRadarTracks", "0"),
    ("HyundaiRadarTracksToggle", "0"),
  ]

  if params.get_bool("RecordFrontLock"):
    params.put_bool("RecordFront", True)

  # set unset params
  for k, v in (default_params + chubbs_default_params):
    if params.get(k) is None:
      params.put(k, v)

  # Create folders needed for msgq
  try:
    os.mkdir(Paths.shm_path())
  except FileExistsError:
    pass
  except PermissionError:
    print(f"WARNING: failed to make {Paths.shm_path()}")

  # set params
  serial = HARDWARE.get_serial()
  params.put("Version", build_metadata.openpilot.version)
  params.put("TermsVersion", terms_version)
  params.put("TrainingVersion", training_version)
  params.put("GitCommit", build_metadata.openpilot.git_commit)
  params.put("GitCommitDate", build_metadata.openpilot.git_commit_date)
  params.put("GitBranch", build_metadata.channel)
  params.put("GitRemote", build_metadata.openpilot.git_origin)
  params.put_bool("IsTestedBranch", build_metadata.tested_channel)
  params.put_bool("IsReleaseBranch", build_metadata.release_channel)
  params.put("HardwareSerial", serial)

  # set dongle id
  reg_res = register(show_spinner=True)
  if reg_res:
    dongle_id = reg_res
  else:
    raise Exception(f"Registration failed for device {serial}")
  os.environ['DONGLE_ID'] = dongle_id  # Needed for swaglog
  os.environ['GIT_ORIGIN'] = build_metadata.openpilot.git_normalized_origin # Needed for swaglog
  os.environ['GIT_BRANCH'] = build_metadata.channel # Needed for swaglog
  os.environ['GIT_COMMIT'] = build_metadata.openpilot.git_commit # Needed for swaglog

  if not build_metadata.openpilot.is_dirty:
    os.environ['CLEAN'] = '1'

  # init logging
  sentry.init(sentry.SentryProject.SELFDRIVE)
  cloudlog.bind_global(dongle_id=dongle_id,
                       version=build_metadata.openpilot.version,
                       origin=build_metadata.openpilot.git_normalized_origin,
                       branch=build_metadata.channel,
                       commit=build_metadata.openpilot.git_commit,
                       dirty=build_metadata.openpilot.is_dirty,
                       device=HARDWARE.get_device_type())

  # preimport all processes
  for p in managed_processes.values():
    p.prepare()


def manager_cleanup() -> None:
  # send signals to kill all procs
  for p in managed_processes.values():
    p.stop(block=False)

  # ensure all are killed
  for p in managed_processes.values():
    p.stop(block=True)

  cloudlog.info("everything is dead")


def manager_thread() -> None:
  cloudlog.bind(daemon="manager")
  cloudlog.info("manager start")
  cloudlog.info({"environ": os.environ})

  params = Params()

  ignore: list[str] = []
  if params.get("DongleId", encoding='utf8') in (None, UNREGISTERED_DONGLE_ID):
    ignore += ["manage_athenad", "uploader"]
  if os.getenv("NOBOARD") is not None:
    ignore.append("pandad")
  ignore += [x for x in os.getenv("BLOCK", "").split(",") if len(x) > 0]

  sm = messaging.SubMaster(['deviceState', 'carParams'], poll='deviceState')
  pm = messaging.PubMaster(['managerState'])

  write_onroad_params(False, params)
  ensure_running(managed_processes.values(), False, params=params, CP=sm['carParams'], not_run=ignore)

  started_prev = False

  while True:
    sm.update(1000)

    started = sm['deviceState'].started

    if started and not started_prev:
      params.clear_all(ParamKeyType.CLEAR_ON_ONROAD_TRANSITION)
    elif not started and started_prev:
      params.clear_all(ParamKeyType.CLEAR_ON_OFFROAD_TRANSITION)

    # update onroad params, which drives pandad's safety setter thread
    if started != started_prev:
      write_onroad_params(started, params)

    started_prev = started

    ensure_running(managed_processes.values(), started, params=params, CP=sm['carParams'], not_run=ignore)

    running = ' '.join("{}{}\u001b[0m".format("\u001b[32m" if p.proc.is_alive() else "\u001b[31m", p.name)
                       for p in managed_processes.values() if p.proc)
    print(running)
    cloudlog.debug(running)

    # send managerState
    msg = messaging.new_message('managerState', valid=True)
    msg.managerState.processes = [p.get_process_state_msg() for p in managed_processes.values()]
    pm.send('managerState', msg)

    # Exit main loop when uninstall/shutdown/reboot is needed
    shutdown = False
    for param in ("DoUninstall", "DoShutdown", "DoReboot"):
      if params.get_bool(param):
        shutdown = True
        params.put("LastManagerExitReason", f"{param} {datetime.datetime.now()}")
        cloudlog.warning(f"Shutting down manager - {param} set")

    if shutdown:
      break


def main() -> None:
  manager_init()
  if os.getenv("PREPAREONLY") is not None:
    return

  # SystemExit on sigterm
  signal.signal(signal.SIGTERM, lambda signum, frame: sys.exit(1))

  try:
    manager_thread()
  except Exception:
    traceback.print_exc()
    sentry.capture_exception()
  finally:
    manager_cleanup()

  params = Params()
  if params.get_bool("DoUninstall"):
    cloudlog.warning("uninstalling")
    HARDWARE.uninstall()
  elif params.get_bool("DoReboot"):
    cloudlog.warning("reboot")
    HARDWARE.reboot()
  elif params.get_bool("DoShutdown"):
    cloudlog.warning("shutdown")
    HARDWARE.shutdown()


if __name__ == "__main__":
  unblock_stdout()

  try:
    main()
  except KeyboardInterrupt:
    print("got CTRL-C, exiting")
  except Exception:
    add_file_handler(cloudlog)
    cloudlog.exception("Manager failed to start")

    try:
      managed_processes['ui'].stop()
    except Exception:
      pass

    # Show last 3 lines of traceback
    error = traceback.format_exc(-3)
    error = "Manager failed to start\n\n" + error
    with TextWindow(error) as t:
      t.wait_for_exit()

    raise

  # manual exit because we are forked
  sys.exit(0)
