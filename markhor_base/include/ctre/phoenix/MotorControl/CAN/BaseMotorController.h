#pragma once

#include "ctre/phoenix/ErrorCode.h"
#include "ctre/phoenix/paramEnum.h"
#include "ctre/phoenix/core/GadgeteerUartClient.h"
#include "ctre/phoenix/MotorControl/IMotorController.h"
#include "ctre/phoenix/MotorControl/ControlMode.h"
#include "ctre/phoenix/MotorControl/DemandType.h"
#include "ctre/phoenix/MotorControl/Faults.h"
#include "ctre/phoenix/MotorControl/FollowerType.h"
#include "ctre/phoenix/MotorControl/StickyFaults.h"
#include "ctre/phoenix/MotorControl/VelocityMeasPeriod.h"
#include "ctre/phoenix/Motion/TrajectoryPoint.h"
#include "ctre/phoenix/Motion/MotionProfileStatus.h"
#include "ctre/phoenix/Motion/MotionProfileStatus.h"
#include "ctre/phoenix/LowLevel/CANBusAddressable.h"
#include "ctre/phoenix/CustomParamConfiguration.h"
#if defined(CTR_INCLUDE_WPILIB_CLASSES) || defined(__FRC_ROBORIO__)
/* WPILIB */
#include "SpeedController.h"
#endif


#include <string>

/* forward proto's */
namespace ctre {
namespace phoenix {
namespace motorcontrol {
namespace lowlevel {
class MotControllerWithBuffer_LowLevel;
class MotController_LowLevel;
}
}
}
}

namespace ctre {
namespace phoenix {
namespace motorcontrol {
namespace can {

struct BasePIDSetConfiguration {

	double selectedFeedbackCoefficient;

	BasePIDSetConfiguration() :
		selectedFeedbackCoefficient(1.0)
	{
	}
    std::string toString(const std::string &prependString) {
        return prependString + ".selectedFeedbackCoefficient = " + std::to_string(selectedFeedbackCoefficient) + ";\n";
    
    }
};// struct BasePIDSetConfiguration
struct FilterConfiguration {

	int remoteSensorDeviceID; 
	RemoteSensorSource remoteSensorSource;  

    FilterConfiguration() :
        remoteSensorDeviceID(0), 
        remoteSensorSource(RemoteSensorSource::RemoteSensorSource_Off) 	
    {
    }
    std::string toString(std::string prependString) {
        std::string retstr = prependString + ".remoteSensorDeviceID = " + std::to_string(remoteSensorDeviceID) + ";\n";
        retstr += prependString + ".remoteSensorSource = " + RemoteSensorSourceRoutines::toString(remoteSensorSource) + ";\n";
        return retstr;
    }

}; // struct FilterConfiguration
struct SlotConfiguration{

	double kP; 
	double kI; 
	double kD; 
	double kF; 
	int integralZone; 
	int allowableClosedloopError; 
	double maxIntegralAccumulator; 
	double closedLoopPeakOutput;
	int closedLoopPeriod;
		
	SlotConfiguration() : 
		kP(0.0), 
		kI(0.0),
		kD(0.0),
		kF(0.0),
		integralZone(0.0), 
		allowableClosedloopError(0.0), 
		maxIntegralAccumulator(0.0),
		closedLoopPeakOutput(1.0),
		closedLoopPeriod(1)
	{
	}
    std::string toString(std::string prependString) {

        std::string retstr = prependString + ".kP = " + std::to_string(kP) + ";\n"; 
        retstr += prependString + ".kI = " + std::to_string(kI) + ";\n"; 
        retstr += prependString + ".kD = " + std::to_string(kD) + ";\n"; 
        retstr += prependString + ".kF = " + std::to_string(kF) + ";\n"; 
        retstr += prependString + ".integralZone = " + std::to_string(integralZone) + ";\n"; 
        retstr += prependString + ".allowableClosedloopError = " + std::to_string(allowableClosedloopError) + ";\n"; 
        retstr += prependString + ".maxIntegralAccumulator = " + std::to_string(maxIntegralAccumulator) + ";\n"; 
        retstr += prependString + ".closedLoopPeakOutput = " + std::to_string(closedLoopPeakOutput) + ";\n";
        retstr += prependString + ".closedLoopPeriod = " + std::to_string(closedLoopPeriod) + ";\n";

        return retstr;

    }
};// struct BaseSlotConfiguration


struct BaseMotorControllerConfiguration : ctre::phoenix::CustomParamConfiguration {
	double openloopRamp;
	double closedloopRamp; 
	double peakOutputForward;
	double peakOutputReverse;
	double nominalOutputForward; 
	double nominalOutputReverse; 
	double neutralDeadband;
	double voltageCompSaturation; 
	int voltageMeasurementFilter;
    VelocityMeasPeriod velocityMeasurementPeriod; 
	int velocityMeasurementWindow; 
	int forwardLimitSwitchDeviceID; //Limit Switch device id isn't used unless device is a remote
	int reverseLimitSwitchDeviceID;
	LimitSwitchNormal forwardLimitSwitchNormal;
	LimitSwitchNormal reverseLimitSwitchNormal;
	int forwardSoftLimitThreshold; 
	int reverseSoftLimitThreshold; 
	bool forwardSoftLimitEnable; 
	bool reverseSoftLimitEnable; 
	SlotConfiguration slot_0;
	SlotConfiguration slot_1;
	SlotConfiguration slot_2;
	SlotConfiguration slot_3;
	bool auxPIDPolarity; 
	FilterConfiguration filter_0;
	FilterConfiguration filter_1;
    int motionCruiseVelocity; 
	int motionAcceleration; 
	int motionProfileTrajectoryPeriod; 
    bool feedbackNotContinuous;
    bool remoteSensorClosedLoopDisableNeutralOnLOS;
    bool clearPositionOnLimitF;
    bool clearPositionOnLimitR;
    bool clearPositionOnQuadIdx;
    bool limitSwitchDisableNeutralOnLOS;
    bool softLimitDisableNeutralOnLOS;
    int pulseWidthPeriod_EdgesPerRot;
    int pulseWidthPeriod_FilterWindowSz;

    BaseMotorControllerConfiguration() :
        openloopRamp(0.0),
        closedloopRamp(0.0),
        peakOutputForward(1.0),
        peakOutputReverse(-1.0),
        nominalOutputForward(0.0),
        nominalOutputReverse(0.0),
        neutralDeadband(0.04),
        voltageCompSaturation(0.0),
        voltageMeasurementFilter(32),
        velocityMeasurementPeriod(Period_100Ms),
        velocityMeasurementWindow(64),
        forwardLimitSwitchDeviceID(0),
        reverseLimitSwitchDeviceID(0),
        forwardLimitSwitchNormal(LimitSwitchNormal_NormallyOpen), 
        reverseLimitSwitchNormal(LimitSwitchNormal_NormallyOpen), 
        forwardSoftLimitThreshold(0),
        reverseSoftLimitThreshold(0), 
        forwardSoftLimitEnable(false),
        reverseSoftLimitEnable(false),
        auxPIDPolarity(false), 
        motionCruiseVelocity(0),
        motionAcceleration(0),
        motionProfileTrajectoryPeriod(0),
        feedbackNotContinuous(false),
        remoteSensorClosedLoopDisableNeutralOnLOS(false),
        clearPositionOnLimitF(false),
        clearPositionOnLimitR(false),
        clearPositionOnQuadIdx(false),
        limitSwitchDisableNeutralOnLOS(false),
        softLimitDisableNeutralOnLOS(false),
        pulseWidthPeriod_EdgesPerRot(1),
        pulseWidthPeriod_FilterWindowSz(1)

	{
	}
    std::string toString(std::string prependString) {

        std::string retstr = prependString + ".openloopRamp = " + std::to_string(openloopRamp) + ";\n";
        retstr += prependString + ".closedloopRamp = " + std::to_string(closedloopRamp) + ";\n"; 
        retstr += prependString + ".peakOutputForward = " + std::to_string(peakOutputForward) + ";\n";
        retstr += prependString + ".peakOutputReverse = " + std::to_string(peakOutputReverse) + ";\n";
        retstr += prependString + ".nominalOutputForward = " + std::to_string(nominalOutputForward) + ";\n"; 
        retstr += prependString + ".nominalOutputReverse = " + std::to_string(nominalOutputReverse) + ";\n"; 
        retstr += prependString + ".neutralDeadband = " + std::to_string(neutralDeadband) + ";\n";
        retstr += prependString + ".voltageCompSaturation = " + std::to_string(voltageCompSaturation) + ";\n"; 
        retstr += prependString + ".voltageMeasurementFilter = " + std::to_string(voltageMeasurementFilter) + ";\n";
        retstr += prependString + ".velocityMeasurementPeriod = " + VelocityMeasPeriodRoutines::toString(velocityMeasurementPeriod) + ";\n"; 
        retstr += prependString + ".velocityMeasurementWindow = " + std::to_string(velocityMeasurementWindow) + ";\n"; 
        retstr += prependString + ".forwardLimitSwitchDeviceID = " + std::to_string(forwardLimitSwitchDeviceID) + ";\n";
        retstr += prependString + ".reverseLimitSwitchDeviceID = " + std::to_string(reverseLimitSwitchDeviceID) + ";\n";
        retstr += prependString + ".forwardLimitSwitchNormal = " + LimitSwitchRoutines::toString(forwardLimitSwitchNormal) + ";\n";
        retstr += prependString + ".reverseLimitSwitchNormal = " + LimitSwitchRoutines::toString(reverseLimitSwitchNormal) + ";\n";
        retstr += prependString + ".forwardSoftLimitThreshold = " + std::to_string(forwardSoftLimitThreshold) + ";\n"; 
        retstr += prependString + ".reverseSoftLimitThreshold = " + std::to_string(reverseSoftLimitThreshold) + ";\n"; 
        retstr += prependString + ".forwardSoftLimitEnable = " + std::to_string(forwardSoftLimitEnable) + ";\n"; 
        retstr += prependString + ".reverseSoftLimitEnable = " + std::to_string(reverseSoftLimitEnable) + ";\n"; 
        retstr += slot_0.toString(prependString + ".slot_0");
        retstr += slot_1.toString(prependString + ".slot_1");
        retstr += slot_2.toString(prependString + ".slot_2");
        retstr += slot_3.toString(prependString + ".slot_3");
        retstr += prependString + ".auxPIDPolarity = " + std::to_string(auxPIDPolarity) + ";\n"; 
        retstr += filter_0.toString(prependString + ".filter_0");
        retstr += filter_1.toString(prependString + ".filter_1");
        retstr += prependString + ".motionCruiseVelocity = " + std::to_string(motionCruiseVelocity) + ";\n"; 
        retstr += prependString + ".motionAcceleration = " + std::to_string(motionAcceleration) + ";\n"; 
        retstr += prependString + ".motionProfileTrajectoryPeriod = " + std::to_string(motionProfileTrajectoryPeriod) + ";\n"; 
        retstr += prependString + ".feedbackNotContinuous = " + std::to_string(feedbackNotContinuous) + ";\n";
        retstr += prependString + ".remoteSensorClosedLoopDisableNeutralOnLOS = " + std::to_string(remoteSensorClosedLoopDisableNeutralOnLOS) + ";\n";
        retstr += prependString + ".clearPositionOnLimitF = " + std::to_string(clearPositionOnLimitF) + ";\n";
        retstr += prependString + ".clearPositionOnLimitR = " + std::to_string(clearPositionOnLimitR) + ";\n";
        retstr += prependString + ".clearPositionOnQuadIdx = " + std::to_string(clearPositionOnQuadIdx) + ";\n";
        retstr += prependString + ".limitSwitchDisableNeutralOnLOS = " + std::to_string(limitSwitchDisableNeutralOnLOS) + ";\n";
        retstr += prependString + ".softLimitDisableNeutralOnLOS = " + std::to_string(softLimitDisableNeutralOnLOS) + ";\n";
        retstr += prependString + ".pulseWidthPeriod_EdgesPerRot = " + std::to_string(pulseWidthPeriod_EdgesPerRot) + ";\n";
        retstr += prependString + ".pulseWidthPeriod_FilterWindowSz = " + std::to_string(pulseWidthPeriod_FilterWindowSz) + ";\n";

        retstr += CustomParamConfiguration::toString(prependString);

        return retstr;
    }
};// struct BaseMotorControllerConfiguration

/**
 * Base motor controller features for all CTRE CAN motor controllers.
 */
class BaseMotorController: public virtual IMotorController {
private:
	ControlMode m_controlMode = ControlMode::PercentOutput;
	ControlMode m_sendMode = ControlMode::PercentOutput;

	int _arbId = 0;
	double m_setPoint = 0;
	bool _invert = false;

protected:
	void* m_handle;
	void* GetHandle();
	virtual ctre::phoenix::ErrorCode BaseConfigAllSettings(const BaseMotorControllerConfiguration &allConfigs, int timeoutMs);
	virtual void BaseGetAllConfigs(BaseMotorControllerConfiguration &allConfigs, int timeoutMs);
	virtual ctre::phoenix::ErrorCode BaseConfigurePID(const BasePIDSetConfiguration &pid, int pidIdx, int timeoutMs);
	virtual void BaseGetPIDConfigs(BasePIDSetConfiguration &pid, int pidIdx, int timeoutMs);
public:
	BaseMotorController(int arbId);
	~BaseMotorController();
	BaseMotorController() = delete;
	BaseMotorController(BaseMotorController const&) = delete;
	BaseMotorController& operator=(BaseMotorController const&) = delete;
	int GetDeviceID();
	virtual void Set(ControlMode Mode, double value);
	virtual void Set(ControlMode mode, double demand0, double demand1);
	virtual void Set(ControlMode mode, double demand0, DemandType demand1Type, double demand1);
	virtual void NeutralOutput();
	virtual void SetNeutralMode(NeutralMode neutralMode);
	void EnableHeadingHold(bool enable);
	void SelectDemandType(bool value);
	//------ Invert behavior ----------//
	virtual void SetSensorPhase(bool PhaseSensor);
	virtual void SetInverted(bool invert);
	virtual bool GetInverted() const;
	//----- Factory Default Configuration -----//
	virtual ctre::phoenix::ErrorCode ConfigFactoryDefault(int timeoutMs = 50);
	//----- general output shaping ------------------//
	virtual ctre::phoenix::ErrorCode ConfigOpenloopRamp(double secondsFromNeutralToFull,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigClosedloopRamp(double secondsFromNeutralToFull,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigPeakOutputForward(double percentOut, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigPeakOutputReverse(double percentOut, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigNominalOutputForward(double percentOut,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigNominalOutputReverse(double percentOut,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigNeutralDeadband(double percentDeadband,
			int timeoutMs = 0);
	//------ Voltage Compensation ----------//
	virtual ctre::phoenix::ErrorCode ConfigVoltageCompSaturation(double voltage, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigVoltageMeasurementFilter(int filterWindowSamples,
			int timeoutMs = 0);
	virtual void EnableVoltageCompensation(bool enable);
	//------ General Status ----------//
	virtual double GetBusVoltage();
	virtual double GetMotorOutputPercent();
	virtual double GetMotorOutputVoltage();
	virtual double GetOutputCurrent();
	virtual double GetTemperature();
	//------ sensor selection ----------//
	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackSensor(
			RemoteFeedbackDevice feedbackDevice, int pidIdx = 0, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackSensor(
			FeedbackDevice feedbackDevice, int pidIdx = 0, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigSelectedFeedbackCoefficient(
			double coefficient, int pidIdx = 0, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigRemoteFeedbackFilter(int deviceID,
			RemoteSensorSource remoteSensorSource, int remoteOrdinal,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigSensorTerm(SensorTerm sensorTerm,
			FeedbackDevice feedbackDevice, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigSensorTerm(SensorTerm sensorTerm,
			RemoteFeedbackDevice feedbackDevice, int timeoutMs = 0);

	//------- sensor status --------- //
	virtual int GetSelectedSensorPosition(int pidIdx = 0);
	virtual int GetSelectedSensorVelocity(int pidIdx = 0);
	virtual ctre::phoenix::ErrorCode SetSelectedSensorPosition(int sensorPos, int pidIdx = 0, int timeoutMs = 50);
	//------ status frame period changes ----------//
	virtual ctre::phoenix::ErrorCode SetControlFramePeriod(ControlFrame frame, int periodMs);
	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrame frame, int periodMs,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode SetStatusFramePeriod(StatusFrameEnhanced frame,
			int periodMs, int timeoutMs = 0);
	virtual int GetStatusFramePeriod(StatusFrame frame, int timeoutMs = 0);
	virtual int GetStatusFramePeriod(StatusFrameEnhanced frame, int timeoutMs = 0);
	//----- velocity signal conditionaing ------//
	virtual ctre::phoenix::ErrorCode ConfigVelocityMeasurementPeriod(VelocityMeasPeriod period,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigVelocityMeasurementWindow(int windowSize,
			int timeoutMs = 0);
	//------ remote limit switch ----------//
	virtual ctre::phoenix::ErrorCode ConfigForwardLimitSwitchSource(
			RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigReverseLimitSwitchSource(
			RemoteLimitSwitchSource type, LimitSwitchNormal normalOpenOrClose,
			int deviceID, int timeoutMs = 0);
	void OverrideLimitSwitchesEnable(bool enable);
	//------ local limit switch ----------//
	virtual ctre::phoenix::ErrorCode ConfigForwardLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigReverseLimitSwitchSource(LimitSwitchSource type,
			LimitSwitchNormal normalOpenOrClose, int timeoutMs = 0);
	//------ soft limit ----------//
	virtual ctre::phoenix::ErrorCode ConfigForwardSoftLimitThreshold(int forwardSensorLimit,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigReverseSoftLimitThreshold(int reverseSensorLimit,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigForwardSoftLimitEnable(bool enable,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigReverseSoftLimitEnable(bool enable,
			int timeoutMs = 0);		
	virtual void OverrideSoftLimitsEnable(bool enable);
	//------ Current Lim ----------//
	/* not available in base */
	//------ General Close loop ----------//
	virtual ctre::phoenix::ErrorCode Config_kP(int slotIdx, double value, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode Config_kI(int slotIdx, double value, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode Config_kD(int slotIdx, double value, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode Config_kF(int slotIdx, double value, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode Config_IntegralZone(int slotIdx, int izone,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigAllowableClosedloopError(int slotIdx,
			int allowableCloseLoopError, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigMaxIntegralAccumulator(int slotIdx, double iaccum,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigClosedLoopPeakOutput(int slotIdx, double percentOut, int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigClosedLoopPeriod(int slotIdx, int loopTimeMs, int timeoutMs = 0);

	virtual ctre::phoenix::ErrorCode ConfigAuxPIDPolarity(bool invert, int timeoutMs = 0);

	//------ Close loop State ----------//
	virtual ctre::phoenix::ErrorCode SetIntegralAccumulator(double iaccum, int pidIdx = 0,int timeoutMs = 0);
	virtual int GetClosedLoopError(int pidIdx = 0);
	virtual double GetIntegralAccumulator(int pidIdx = 0);
	virtual double GetErrorDerivative(int pidIdx = 0);

	virtual ctre::phoenix::ErrorCode SelectProfileSlot(int slotIdx, int pidIdx);

	virtual int GetClosedLoopTarget(int pidIdx = 0);
	virtual int GetActiveTrajectoryPosition();
	virtual int GetActiveTrajectoryVelocity();
	virtual double GetActiveTrajectoryHeading();

	//------ Motion Profile Settings used in Motion Magic  ----------//
	virtual ctre::phoenix::ErrorCode ConfigMotionCruiseVelocity(int sensorUnitsPer100ms,
			int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ConfigMotionAcceleration(int sensorUnitsPer100msPerSec,
			int timeoutMs = 0);
	//------ Motion Profile Buffer ----------//
	virtual ErrorCode ClearMotionProfileTrajectories();
	virtual int GetMotionProfileTopLevelBufferCount();
	virtual ctre::phoenix::ErrorCode PushMotionProfileTrajectory(
			const ctre::phoenix::motion::TrajectoryPoint & trajPt);
	virtual bool IsMotionProfileTopLevelBufferFull();
	virtual void ProcessMotionProfileBuffer();
	virtual ctre::phoenix::ErrorCode GetMotionProfileStatus(
			ctre::phoenix::motion::MotionProfileStatus & statusToFill);
	virtual ctre::phoenix::ErrorCode ClearMotionProfileHasUnderrun(int timeoutMs = 0);
	virtual ctre::phoenix::ErrorCode ChangeMotionControlFramePeriod(int periodMs);
	virtual ctre::phoenix::ErrorCode ConfigMotionProfileTrajectoryPeriod(int baseTrajDurationMs, int timeoutMs = 0);
	

    //------Feedback Device Interaction Settings---------//
    virtual ErrorCode ConfigFeedbackNotContinuous(bool feedbackNotContinuous, int timeoutMs = 0);
    virtual ErrorCode ConfigRemoteSensorClosedLoopDisableNeutralOnLOS(bool remoteSensorClosedLoopDisableNeutralOnLOS, int timeoutMs = 0);
    virtual ErrorCode ConfigClearPositionOnLimitF(bool clearPositionOnLimitF, int timeoutMs = 0);
    virtual ErrorCode ConfigClearPositionOnLimitR(bool clearPositionOnLimitR, int timeoutMs = 0);
    virtual ErrorCode ConfigClearPositionOnQuadIdx(bool clearPositionOnQuadIdx, int timeoutMs = 0);
    virtual ErrorCode ConfigLimitSwitchDisableNeutralOnLOS(bool limitSwitchDisableNeutralOnLOS, int timeoutMs = 0);
    virtual ErrorCode ConfigSoftLimitDisableNeutralOnLOS(bool foftLimitDisableNeutralOnLOS, int timeoutMs = 0);
    virtual ErrorCode ConfigPulseWidthPeriod_EdgesPerRot(int pulseWidthPeriod_EdgesPerRot, int timeoutMs = 0);
    virtual ErrorCode ConfigPulseWidthPeriod_FilterWindowSz(int pulseWidthPeriod_FilterWindowSz, int timeoutMs = 0);

    //------ error ----------//
	virtual ctre::phoenix::ErrorCode GetLastError();
	//------ Faults ----------//
	virtual ctre::phoenix::ErrorCode GetFaults(Faults & toFill);
	virtual ctre::phoenix::ErrorCode GetStickyFaults(StickyFaults & toFill);
	virtual ctre::phoenix::ErrorCode ClearStickyFaults(int timeoutMs = 0);
	//------ Firmware ----------//
	virtual int GetFirmwareVersion();
	virtual bool HasResetOccurred();
	//------ Custom Persistent Params ----------//
	virtual ctre::phoenix::ErrorCode ConfigSetCustomParam(int newValue, int paramIndex,
			int timeoutMs = 0);
	virtual int ConfigGetCustomParam(int paramIndex,
			int timeoutMs = 0);
	//------ Generic Param API, typically not used ----------//
	virtual ctre::phoenix::ErrorCode ConfigSetParameter(ctre::phoenix::ParamEnum param, double value,
			uint8_t subValue, int ordinal, int timeoutMs = 0);
	virtual double ConfigGetParameter(ctre::phoenix::ParamEnum param, int ordinal, int timeoutMs = 0);
	//------ Misc. ----------//
	virtual int GetBaseID();
	virtual ControlMode GetControlMode();
	// ----- Follower ------//
	void Follow(IMotorController & masterToFollow, ctre::phoenix::motorcontrol::FollowerType followerType);
	virtual void Follow(IMotorController & masterToFollow);
	virtual void ValueUpdated();

	
	//-------Config All----------//
	ctre::phoenix::ErrorCode ConfigureSlot(const SlotConfiguration &slot, int slotIdx = 0, int timeoutMs = 50);	
	void GetSlotConfigs(SlotConfiguration &slot, int slotIdx = 0, int timeoutMs = 50);	
	ctre::phoenix::ErrorCode ConfigureFilter(const FilterConfiguration &filter, int ordinal = 0, int timeoutMs = 50);	
	void GetFilterConfigs(FilterConfiguration &Filter, int ordinal = 0, int timeoutMs = 50);
	
};// class BaseMotorController
} // namespace can
} // namespace motorcontrol
} // namespace phoenix
} // namespace ctre
