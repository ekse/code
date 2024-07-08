using System;

class RemoteControlCar
{
    private int _batteryCharge = 100;
    private readonly int _batteryDrain;
    private int _speed;
    private int _distanceDrivenInMeters;

    public RemoteControlCar(int speed, int batteryDrain)
    {
        this._batteryDrain = batteryDrain;
        this._speed = speed;
    }

    public bool BatteryDrained()
    {
        return _batteryCharge < _batteryDrain;
    }

    public int DistanceDriven()
    {
        return this._distanceDrivenInMeters;
    }

    public void Drive()
    {
        if (BatteryDrained())
        {
            return;
        }

        this._distanceDrivenInMeters += _speed;
        this._batteryCharge -= _batteryDrain;
    }

    public static RemoteControlCar Nitro()
    {
        return new RemoteControlCar(50, 4);
    }
}

class RaceTrack
{
    private readonly int _distance;
    public RaceTrack(int distance)
    {
        this._distance = distance;
    }

    public bool TryFinishTrack(RemoteControlCar car)
    {
        while (!car.BatteryDrained())
        {
            if (car.DistanceDriven() >= this._distance)
            {
                return true;
            }

            car.Drive();
        }

        return car.DistanceDriven() >= this._distance;
    }
}
