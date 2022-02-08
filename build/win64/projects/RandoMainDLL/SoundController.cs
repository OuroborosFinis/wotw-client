using NAudio.Wave;
using System;

namespace RandoMainDLL
{
    public static class SoundController
    {
        public static void Play(string file)
        {
            using (var audioFile = new AudioFileReader(file))
            using (var outputDevice = new WaveOutEvent())
            {
                outputDevice.Init(audioFile);
                outputDevice.Play();
            }
        }
    }
}
