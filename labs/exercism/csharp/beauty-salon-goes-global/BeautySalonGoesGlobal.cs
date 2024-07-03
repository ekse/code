using System;
using System.Runtime.InteropServices;

public enum Location
{
    NewYork,
    London,
    Paris
}

public enum AlertLevel
{
    Early,
    Standard,
    Late
}

public static class Appointment
{
    public static DateTime ShowLocalTime(DateTime dtUtc) => dtUtc.ToLocalTime();

    private static TimeZoneInfo GetTimeZoneForLocation(Location location)
    {
        TimeZoneInfo timezone;

        if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
        {
            timezone = location switch
            {
                Location.NewYork => TimeZoneInfo.FindSystemTimeZoneById("Eastern Standard Time"),
                Location.London => TimeZoneInfo.FindSystemTimeZoneById("GMT Standard Time"),
                Location.Paris => TimeZoneInfo.FindSystemTimeZoneById("W. Europe Standard Time"),
                _ => throw new NotImplementedException(),
            };
        }
        else
        {
            timezone = location switch
            {
                Location.NewYork => TimeZoneInfo.FindSystemTimeZoneById("America/New_York"),
                Location.London => TimeZoneInfo.FindSystemTimeZoneById("Europe/London"),
                Location.Paris => TimeZoneInfo.FindSystemTimeZoneById("Europe/Paris"),
                _ => throw new NotImplementedException(),
            };
        }

        return timezone;
    }

    public static DateTime Schedule(string appointmentDateDescription, Location location)
    {
        TimeZoneInfo timezone = GetTimeZoneForLocation(location);
        DateTime time = DateTime.Parse(appointmentDateDescription);
        return TimeZoneInfo.ConvertTimeToUtc(time, timezone);

    }

    public static DateTime GetAlertTime(DateTime appointment, AlertLevel alertLevel)
    {
        TimeSpan timespan = alertLevel switch
        {
            AlertLevel.Early => TimeSpan.FromDays(1),
            AlertLevel.Standard => TimeSpan.FromMinutes(105),
            AlertLevel.Late => TimeSpan.FromMinutes(30),
            _ => throw new NotImplementedException(),
        };

        return appointment - timespan;
    }

    public static bool HasDaylightSavingChanged(DateTime dt, Location location)
    {
        TimeZoneInfo timezone = GetTimeZoneForLocation(location);
        return timezone.IsDaylightSavingTime(dt) != timezone.IsDaylightSavingTime(dt - TimeSpan.FromDays(7));

    }

    public static DateTime NormalizeDateTime(string dtStr, Location location)
    {
        System.Globalization.CultureInfo cultureinfo = location switch
        {
            Location.NewYork => new System.Globalization.CultureInfo("en-US"),
            Location.London => new System.Globalization.CultureInfo("en-GB"),
            Location.Paris => new System.Globalization.CultureInfo("fr-FR"),
            _ => throw new NotImplementedException(),
        };

        DateTime dt;
        return DateTime.TryParse(dtStr, cultureinfo, out dt) ? dt : new DateTime(1, 1, 1, 0, 0, 0);
        

    }
}
