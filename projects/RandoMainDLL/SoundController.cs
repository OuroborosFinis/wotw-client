using System;
using System.IO;
using System.Threading;
using NAudio.Wave;

namespace RandoMainDLL {
  public static class SoundController {
    public static void Play(string file) {
      var thread = new Thread(() => {
        var randomNumber = (new Random()).Next(4) + 1;
        var audioFile = new AudioFileReader(Path.Combine(Randomizer.BasePath, file.Replace("%%", randomNumber.ToString())));
        var outputDevice = new WasapiOut();
        outputDevice.Init(audioFile);
        outputDevice.Play();

        while (outputDevice.PlaybackState == PlaybackState.Playing) {
          Thread.Sleep(1000);
        }

        outputDevice.Dispose();
      });
      thread.Start();
    }
  }
}
