using System;
using System.Linq;

public static class TelemetryBuffer
{
    public static byte[] ToBuffer(long reading)
    {
        byte typeRepresensation = reading switch
        {
            /*
             * 4_294_967_296	9_223_372_036_854_775_807	long
                2_147_483_648	4_294_967_295	uint
                65_536	2_147_483_647	int
                0	65_535	ushort
                -32_768	-1	short
                -2_147_483_648	-32_769	int
                -9_223_372_036_854_775_808	-2_147_483_649	long
             */
            >= 4_294_967_296 => 256 - 8,
            >= 2_147_483_648 => 4,
            >= 65_536 => 256 - 4,
            >= 0 => 2,
            >= -32_768 => 256 - 2,
            >= -2_147_483_648 => 256 - 4,
            _ => 256 - 8
        };
        
        byte[] bytes = BitConverter.GetBytes(reading);
        byte[] buffer = new byte[9];
        buffer[0] = typeRepresensation;
        bytes.CopyTo(buffer, 1);
        return buffer;
        
    }

    public static long FromBuffer(byte[] buffer)
    {
        throw new NotImplementedException("Please implement the static TelemetryBuffer.FromBuffer() method");
    }
}
