using System;

class WeighingMachine
{
    public int Precision { get; }

    private double _weight;

    public double TareAdjustment { get; set; } = 5.0;

    public string DisplayWeight
    {
        get
        {
            string formatString = String.Concat("{0:F", Precision, "} kg");
            return String.Format(formatString, _weight - TareAdjustment);
        }  
    } 

    public double Weight
    {
        get => _weight;

        set
        {
            if (value < 0)
                throw new ArgumentOutOfRangeException();
            
            _weight = value;
        }
    }

    public WeighingMachine(int precision)
    {
        Precision = precision;
    }
}
