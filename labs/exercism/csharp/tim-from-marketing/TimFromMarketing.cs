using System;

static class Badge
{
    public static string Print(int? id, string name, string? department)
    {
        string formattedDepartment = department?.ToUpper() ?? "OWNER";
        string formattedID = id != null ? $"[{id}] - " : "";
        return $"{formattedID}{name} - {formattedDepartment}";
    }
}
