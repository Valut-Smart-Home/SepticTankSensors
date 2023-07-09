using System.IO.Ports;

static class Program
{
    static void Main(string[] args)
    {
        var portName = args.Length > 0 ? args[0] : "/dev/ttyS3";
        var sp = new SerialPort(portName, 9600, Parity.None, 8, StopBits.One);

        while (true)
        {
            var readed = new int[3];
            for (int i = 0; i < 3; i++)
            {
                try
                {
                    if (!sp.IsOpen)
                        sp.Open();
                    readed[i] = sp.ReadByte();
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }

            var data = readed[0];
            if (readed.All(x => x == data) && (data & 0x88) == 0x88 && (data | 0x11) == 0)
            {
                var compares = new[] { 1 << 6, 1 << 5, 1 << 2, 1 << 1 };
                var level = compares.Count(x => (x & data) != 0);
                if (level > 0)
                    Console.WriteLine($"Alert - level: {level}");
            }
        }
    }
}