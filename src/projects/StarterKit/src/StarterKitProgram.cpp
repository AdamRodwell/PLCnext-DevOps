#include "StarterKitProgram.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"

namespace StarterKit
{

uint32
StarterKitProgram::convertMillivoltsToRange(uint32 millivolts, uint32 minRange, uint32 maxRange)
{
    double voltage = static_cast<double>(millivolts) / 1000.0;
    double scaled = ((voltage / 10.0) * (maxRange - minRange)) + minRange;
    return static_cast<uint32>(scaled);
}

void
StarterKitProgram::Execute()
{
    try
    {
        if (config_.allowOutputs && command_.setOutput)
        {
            dOUT01_ = true;
            dOUT02_ = true;
        }
        else
        {
            dOUT01_ = false;
            dOUT02_ = false;
        }

        if (command_.readAnalog1)
        {
            uint32 analogReading = aiN1_;
            log.Info("Analog one reading: {0}", analogReading);

            const double scaledReading = convertMillivoltsToRange(
                analogReading, config_.analogInOne.minRange, config_.analogInOne.maxRange);

            log.Info("Scaled analog reading {0}", scaledReading);
        }
    }
    catch (const std::exception& e)
    {
        log.Error("Exception caught in Execute(): {0}", e.what());
    }
    catch (...)
    {
        log.Error("Unknown exception caught in Execute()");
    }
}

} // end of namespace StarterKit
