using System;
using System.IO;
using UnityEngine;
// �αװ� ����Ǵ� local ��ġ
// (����� �̸�)\AppData\LocalLow\(company name)\(product name)\Log


public class Logger
{
    internal static readonly string DefaultLogFileName = "Log";

    internal static void AppendLog(string tag, string message, LogLevel logLevel = LogLevel.Debug)
    {
        // �α׵����͸� ���Ͽ� �����Ѵ�.
        // �α� ������ ������ ������ ����.
        // ('yyyyMMddHHmmss', 'tag', 'Log Level', 'Log Text')
        var filePath = GetOrCreateFilePath(tag);
        FileStream fileStream = new FileStream(filePath, FileMode.Append);
        StreamWriter writer = new StreamWriter(fileStream);

        string[] logTexts = message.Split('\n');     // Ư�� ���ڸ� �������� �߶��ش�.
        foreach (var text in logTexts)
        {
            string writeText = MakeLogText(tag, text, logLevel);
            
            writer.WriteLine(writeText);
        }

        writer.Flush();
        writer.DisposeAsync();
        fileStream.DisposeAsync();
    }

    private static string MakeLogText(string tag, string text, LogLevel logLevel)
    {
        return $"('{GetCurrentTime()}', '{tag}', '{logLevel}', '{text}')";
    }


    // �α׸� ������ ������ �����Ѵ�.
    // ������ �Ϸ翡 �ϳ��� �����Ѵ�.
    // ���� �̸��� ������ Log_LogTag_yyyyMMdd.log
    private static string GetOrCreateFilePath(string tag)
    {
        // ���� ���ο� ������ ������.
        var directoryPath = Path.Combine(Application.persistentDataPath, "Log");
        directoryPath = Path.Combine(directoryPath, GetCurrentDay());
        var fileName = $"{DefaultLogFileName}_{tag}_{GetCurrentDay()}.txt";
        var filePath = Path.Combine(directoryPath, fileName);

        if (!Directory.Exists(directoryPath))
        {
            Directory.CreateDirectory(directoryPath);
        }

        if (!File.Exists(filePath))
        {
            FileStream fileStream = new FileStream(filePath, FileMode.Append);
            StreamWriter writer = new StreamWriter(fileStream);

            writer.Flush();
            writer.DisposeAsync();
            fileStream.DisposeAsync();
        }

        return filePath;
    }

    private static string GetCurrentTime()
    {
        return DateTime.Now.ToString("yyyyMMddHHmmss");
    }

    private static string GetCurrentDay()
    {
        return DateTime.Now.ToString("yyyyMMdd");
    }
}