public enum LogLevel
{
    Unknown = 0,
    Trace = 1,
    Debug = 2,
    Info = 4,
    Warning = 5,
    Error = 6,
    Fatal = 42
}

static class LogLine
{
    private static LogLevel LogLevelFromString(string level)
    {
        return level switch
        {
            "TRC" => LogLevel.Trace,
            "DBG" => LogLevel.Debug,
            "INF" => LogLevel.Info,
            "WRN" => LogLevel.Warning,
            "ERR" => LogLevel.Error,
            "FTL" => LogLevel.Fatal,
            _ => LogLevel.Unknown
        };
    }
    
    public static LogLevel ParseLogLevel(string logLine)
    { 
        return LogLevelFromString(logLine.Substring(1, 3));
    }

    public static string OutputForShortLog(LogLevel logLevel, string message)
    {
        return $"{(int) logLevel}:{message}";
    }
}
