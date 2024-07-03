using System;

static class LogLine
{
    private static string[] SplitLogMessage(string logLine) => logLine.Split(":");

    public static string Message(string logLine)
    {
        string[] logParts = SplitLogMessage(logLine);
        return logParts[1].Trim();
    }

    public static string LogLevel(string logLine)
    {
        string[] logParts = SplitLogMessage(logLine);

        return logParts[0] switch
        {
            "[ERROR]" => "error",
            "[WARNING]" => "warning",
            _ => "info"
        };
    }

    public static string Reformat(string logLine)
    {
        string message = Message(logLine);
        string level = LogLevel(logLine);
        return $"{message} ({level})";
    }
}
