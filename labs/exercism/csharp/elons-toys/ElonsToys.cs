using System;

class RemoteControlCar
{
    int BatteryCharge = 100;
    int DistanceDriven = 0;

    public static RemoteControlCar Buy()
    {
        return new RemoteControlCar();
    }

    public string DistanceDisplay() => $"Driven {DistanceDriven} meters";

    public string BatteryDisplay()
    {
        return BatteryCharge > 0 ? $"Battery at {BatteryCharge}%" : "Battery empty";
    }

    public void Drive()
    {
        if (BatteryCharge == 0)
        {
            return;
        }

        BatteryCharge -= 1;
        DistanceDriven += 20;
    }
}
