public class RemoteControlCar
{
    private enum SpeedUnits
    {
        MetersPerSecond,
        CentimetersPerSecond
    }

    private struct Speed
    {
        public decimal Amount { get; }
        public SpeedUnits SpeedUnits { get; }

        public Speed(decimal amount, SpeedUnits speedUnits)
        {
            Amount = amount;
            SpeedUnits = speedUnits;
        }

        public override string ToString()
        {
            string unitsString = "meters per second";
            if (SpeedUnits == SpeedUnits.CentimetersPerSecond)
            {
                unitsString = "centimeters per second";
            }

            return Amount + " " + unitsString;
        }
    }


    public string CurrentSponsor { get; private set; }

    private Speed currentSpeed;

    public ITelemetry Telemetry {get;}

    public RemoteControlCar()
    {
        Telemetry = new CarTelemetry(this);
    }

    public interface ITelemetry
    {
        void Calibrate();
        bool SelfTest();
        void ShowSponsor(string sponsorName);
        void SetSpeed(decimal amount, string units);
    }

    private class CarTelemetry: ITelemetry
    {
        private readonly RemoteControlCar _car;

        public CarTelemetry(RemoteControlCar car)
        {
            _car = car;
        }

        public void Calibrate()
        {

        }

        public bool SelfTest() => true;

        public void ShowSponsor(string sponsorName) => _car.SetSponsor(sponsorName);

        public void SetSpeed(decimal amount, string unitsString)
        {
            SpeedUnits speedUnits = SpeedUnits.MetersPerSecond;
            if (unitsString == "cps")
            {
                speedUnits = SpeedUnits.CentimetersPerSecond;
            }

            _car.SetSpeed(new Speed(amount, speedUnits));
        }
    }

    public string GetSpeed() => currentSpeed.ToString();

    private void SetSponsor(string sponsorName) => CurrentSponsor = sponsorName;

    private void SetSpeed(Speed speed) => currentSpeed = speed;
}