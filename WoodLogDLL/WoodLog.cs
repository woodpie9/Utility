using System;
using System.IO;
using static System.IO.Directory;
using System.Collections.Concurrent;        // ConCurrentQueue
using System.Threading;                     // Thread
using System.Timers;                        // Timer


namespace WoodLogDLL
{
    public sealed class WoodLog
    {
        private static readonly WoodLog _instance = new WoodLog();

        #region 변수 선언, enum
        private ConcurrentQueue<string> _queueInfo;
        private ConcurrentQueue<string> _queueWarning;
        private ConcurrentQueue<string> _queueError;
        private ConcurrentQueue<string> _queueFatal;
        private ConcurrentQueue<string> _queueDebug;

        private const string LogDir = @"..\..\LOG";
        private const string InfoDir = @"..\..\LOG\Info";
        private const string WarningDir = @"..\..\LOG\Warning";
        private const string ErrorDir = @"..\..\LOG\Error";
        private const string FatalDir = @"..\..\LOG\Fatal";
        private const string DebugDir = @"..\..\LOG\Debug";

        private bool _autoSave;
        private int _saveTime;
        private System_State _state;
        private System.Timers.Timer _autoSaver;

        public enum SeverityToLevel
        {
            Info = 0,
            Warning,
            Error,
            Fatal,
            Debug,
        }
        #endregion

        #region 생성자 소멸자
        // https://csharpindepth.com/Articles/Singleton 의 4번째  싱글톤
        // C# 컴파일러에게 알려주는 명시적 정적 생성자
        static WoodLog()
        {
            // 정적 생성자
            // 클래스의 인스턴스가 생성되거나 정적 맴버가 참조될 때만 실행되고 AppDomain 당 한번만 실행된다.
        }

        private WoodLog()
        {
            // 동적 생성자
            Console.WriteLine("private 생성자");
            _state = System_State.None;
        }

        ~WoodLog()
        {
            WoodLog_PrintFile();
            _state = System_State.None;
        }
        #endregion

        public static WoodLog Instance
        {
            get
            {
                Console.WriteLine("get Woodlog instance");
                return _instance;
            }
        }

        public void WoodLog_Init()
        {
            if (_state == System_State.None)
            {
                Console.WriteLine("Woodlog_Init :: Init");

                _queueInfo = new ConcurrentQueue<string>();
                _queueWarning = new ConcurrentQueue<string>();
                _queueError = new ConcurrentQueue<string>();
                _queueFatal = new ConcurrentQueue<string>();
                _queueDebug = new ConcurrentQueue<string>();

                _state = System_State.Init;
                Thread mkdir = new Thread(() => WoodLog_MakeDir());         // 람다식을 사용해서 스레드 생성
                mkdir.Start();
            }
            else if (_state >= System_State.Init)
            {
                Console.WriteLine("Woodlog_Init :: Already Init");
            }
        }

        public void WoodLog_SetTimer(bool autoSave, int saveSecond = 3)
        {
            if (_state >= System_State.Init)
            {
                _autoSave = autoSave;
                _saveTime = saveSecond * 1000;

                if (_autoSave)
                {
                    // 로그를 자동으로 저장해주는 타이머 스레드 생성
                    Console.WriteLine("WoodLog_SetTimer :: AutoSave On");

                    _autoSaver = new System.Timers.Timer();
                    _autoSaver.Interval = _saveTime;
                    _autoSaver.Elapsed += new ElapsedEventHandler(AutoSave_Elapsed);
                    _autoSaver.Start();
                    _autoSave = false;
                }
                else
                {
                    Console.WriteLine("WoodLog_SetTimer :: AutoSave Off");
                }
            }
            else
            {
                Console.Write("Woodlog_SetTimer :: Pls Woodlog_Init first");
            }

        }

        public void WoodLog_PushLog(SeverityToLevel level, string data, string tag = "Test")
        {
            if (_state >= System_State.Init && _state != System_State.Stop)
            {
                string nowTime = DateTime.Now.ToString("yy-MM-dd-HH-mm-ss");
                Console.WriteLine(nowTime);

                string log = $"('{nowTime}', '{tag}', '{level}', '{data}')";

                switch (level)
                {
                    case SeverityToLevel.Info:
                        _queueInfo.Enqueue(log);
                        break;

                    case SeverityToLevel.Warning:
                        _queueWarning.Enqueue(log);
                        break;

                    case SeverityToLevel.Error:
                        _queueError.Enqueue(log);
                        break;

                    case SeverityToLevel.Fatal:
                        _queueFatal.Enqueue(log);
                        break;

                    case SeverityToLevel.Debug:
                        _queueDebug.Enqueue(log);
                        break;
                }

            }
            else
            {
                Console.Write("Woodlog_SetTimer :: Pls Woodlog_Start first");
            }
        }

        private static string GetCurrentTime()
        {
            return DateTime.Now.ToString("yy-MM-dd-HH-mm-ss");
        }

        public void WoodLog_PrintFile()
        {
            while (_state == System_State.Init)
            {
                Thread.Sleep(100);
            }

            if (_state >= System_State.Mkdir)
            {
                System.Console.WriteLine("WoodLog_PrintFile :: Start PrintFile");

                // C# 에서 현제시간을 가져오기. Date Time 사용
                // https://developer-talk.tistory.com/147

                Console.WriteLine(GetCurrentTime());

                if (_queueInfo.IsEmpty == false)
                {
                    var path = InfoDir + @"\Info-" + GetCurrentTime() + ".log";
                    StreamWriter logWrite = File.CreateText(path);

                    while (_queueInfo.TryDequeue(out var msg))
                    {
                        logWrite.WriteLine(msg);
                    }
                    logWrite.Dispose();
                    System.Console.WriteLine("WoodLog_PrintFile :: Info");
                }

                if (_queueWarning.IsEmpty == false)
                {
                    var path = WarningDir + @"\Warning-" + GetCurrentTime() + ".log";
                    StreamWriter logWrite = File.CreateText(path);

                    while (_queueWarning.TryDequeue(out var msg))
                    {
                        logWrite.WriteLine(msg);
                    }
                    logWrite.Dispose();
                    System.Console.WriteLine("WoodLog_PrintFile :: Warning");
                }

                if (_queueError.IsEmpty == false)
                {
                    var path = ErrorDir + @"\Error-" + GetCurrentTime() + ".log";
                    StreamWriter logWrite = File.CreateText(path);

                    while (_queueError.TryDequeue(out var msg))
                    {
                        logWrite.WriteLine(msg);
                    }
                    logWrite.Dispose();
                    System.Console.WriteLine("WoodLog_PrintFile :: Error");
                }

                if (_queueFatal.IsEmpty == false)
                {
                    var path = FatalDir + @"\Fatal-" + GetCurrentTime() + ".log";
                    StreamWriter logWrite = File.CreateText(path);

                    while (_queueFatal.TryDequeue(out var msg))
                    {
                        logWrite.WriteLine(msg);
                    }
                    logWrite.Dispose();
                    System.Console.WriteLine("WoodLog_PrintFile :: Fatal");
                }

                if (_queueDebug.IsEmpty == false)
                {
                    var path = DebugDir + @"\Debug-" + GetCurrentTime() + ".log";
                    StreamWriter logWrite = File.CreateText(path);

                    while (_queueDebug.TryDequeue(out var msg))
                    {
                        logWrite.WriteLine(msg);
                    }
                    logWrite.Dispose();
                    System.Console.WriteLine("WoodLog_PrintFile :: Debug");
                }
            }
            else
            {
                System.Console.WriteLine("WoodLog_PrintFile :: Pls Woodlog_Init first");
            }
        }

        public void WoodLog_Start()
        {
            if (_state >= System_State.Init)
            {
                _state = System_State.Start;
            }
            else
            {
                System.Console.WriteLine("WoodLog_PrintFile :: Pls Woodlog_Init first");
            }
        }

        public void WoodLog_Stop()
        {
            if (_state >= System_State.Start)
            {
                System.Console.WriteLine("Called WoodLog_Stop");
                _state = System_State.Stop;

                // 자동저장 스레드 종료
                if (_autoSaver == null) return;

                System.Console.WriteLine("AutoSaver Stop");
                _autoSaver.Stop();
            }
            else
            {
                System.Console.WriteLine("WoodLog_PrintFile :: Pls Woodlog_Start first");
            }
        }


        private void WoodLog_MakeDir()
        {
            Console.WriteLine("Woodlog_MakeDir");
            //Stopwatch stopwatch = new Stopwatch();
            //stopwatch.Start();

            if (Exists(LogDir))
            {
                Console.WriteLine("LOG 폴더가 이미 있음");
            }
            else
            {
                CreateDirectory(LogDir);
                Console.WriteLine("폴더 만들기 성공");
            }

            if (Exists(InfoDir))
            {
                Console.WriteLine("InfoDir 이미 있음");
            }
            else
            {
                CreateDirectory(InfoDir);
                Console.WriteLine("InfoDir 폴더 만들기 성공");
            }

            if (Exists(WarningDir))
            {
                Console.WriteLine("WarningDir 이미 있음");
            }
            else
            {
                CreateDirectory(WarningDir);
                Console.WriteLine("WarningDir 만들기 성공");
            }

            if (Exists(ErrorDir))
            {
                Console.WriteLine("ErrorDir 이미 있음");
            }
            else
            {
                CreateDirectory(ErrorDir);
                Console.WriteLine("ErrorDir 만들기 성공");
            }

            if (Exists(FatalDir))
            {
                Console.WriteLine("FatalDir 이미 있음");
            }
            else
            {
                CreateDirectory(FatalDir);
                Console.WriteLine("FatalDir 만들기 성공");
            }

            if (Exists(DebugDir))
            {
                Console.WriteLine("DebugDir 이미 있음");
            }
            else
            {
                CreateDirectory(DebugDir);
                Console.WriteLine("FatalDir 만들기 성공");
            }

            _state = System_State.Mkdir;
        }

        private void AutoSave_Elapsed(object sender, ElapsedEventArgs e)
        {
            System.Console.WriteLine("AutoSave_Elapsed :: Called");

            WoodLog_PrintFile();
        }
    }
}
