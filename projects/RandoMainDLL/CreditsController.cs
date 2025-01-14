﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace RandoMainDLL {
  static class CreditsController {

    public static readonly string CreditsFile = "credits";
    public static readonly int CreditsBaseID = 10000;
    public static float ZValue = 20.0f;

    // TODO: Load this from a file and provide wheel item to reload it in debug mode.
    private static List<Entry> creditsEntries = new List<Entry>();
    private static List<Entry> activeEntries = new List<Entry>();
    private static Dictionary<int, List<string>> collections = new Dictionary<int, List<string>>();
    private static int currentIndex = 0;

    private static bool startedDebug = false;
    private static Random rand;

    private static void Reset() {
      foreach (var entry in activeEntries)
        entry.Reset();

      rand = new Random(0);
      activeEntries.Clear();
      currentIndex = 0;
      if (startedDebug)
        InterOp.Messaging.text_box_destroy(CreditsBaseID);

      startedDebug = false;
    }

    private static void Update(float time) {
      while (creditsEntries.Count > currentIndex && creditsEntries[currentIndex].ShouldResolve(time)) {
        activeEntries.Add(creditsEntries[currentIndex]);
        ++currentIndex;
      }

      for (var i = 0; i < activeEntries.Count; ++i)
        if (activeEntries[i].Resolve(time))
          activeEntries.RemoveAt(i--);

/*      if (Randomizer.Dev) {
        if (!startedDebug) {
          InterOp.Messaging.text_box_create(CreditsBaseID, 0.5f, 0.5f, false, false);
          InterOp.Messaging.text_box_position(CreditsBaseID, 0.0f, 3.5f, ZValue);
          InterOp.Messaging.text_box_alignment(CreditsBaseID, InterOp.Messaging.Alignment.Center);
          InterOp.Messaging.text_box_anchor(CreditsBaseID, InterOp.Messaging.HorizontalAnchor.Center, InterOp.Messaging.VerticalAnchor.Top);
          startedDebug = true;
        }

        InterOp.Messaging.text_box_text(CreditsBaseID, $"Credits progress: {time}");
      }*/
    }

    public static void CreditsProgress(float time) {
      if (time < 0.0f)
        Reset();
      else
        Update(time);
    }

    public static void ReloadFile() {
      if (currentIndex != 0) {
        Randomizer.Warn("CreditsController", "Can't reload while running");
        return;
      }

      rand = new Random(0);
      collections.Clear();
      creditsEntries.Clear();
      if (File.Exists(Randomizer.BasePath + CreditsFile)) {
        foreach (string line in File.ReadLines(Randomizer.BasePath + CreditsFile)) {
          var comment = line.IndexOf("//");
          var uncommented_line = comment < 0 ? line.Trim() : line.Substring(0, comment).Trim();
          if (uncommented_line.Length != 0) {
            var parts = uncommented_line.Split('|');
            var type = parts[0].ParseToInt("CreditsController.Type");
            switch (type) {
              case 1: {
                  if (parts.Length < 7 || parts.Length > 12) {
                    Randomizer.Warn("CreditsController", $"malformed text entry: {uncommented_line}");
                    break;
                  }

                  var startTime = parts[1].ParseToFloat("CreditsController.StartTime");
                  var length = parts[2].ParseToFloat("CreditsController.Length");
                  var id = parts[3].ParseToInt("CreditsController.ID");
                  var x = parts[4].ParseToFloat("CreditsController.X");
                  var y = parts[5].ParseToFloat("CreditsController.Y");
                  var alignment = InterOp.Messaging.Alignment.Center;
                  if (parts.Length > 7)
                    alignment = (InterOp.Messaging.Alignment)parts[7].ParseToInt("CreditsController.Alignment");
                  
                  var horizontal = InterOp.Messaging.HorizontalAnchor.Center;
                  if (parts.Length > 8)
                    horizontal = (InterOp.Messaging.HorizontalAnchor)parts[8].ParseToInt("CreditsController.HorizontalAnchor");

                  var vertical = InterOp.Messaging.VerticalAnchor.Middle;
                  if (parts.Length > 9)
                    vertical = (InterOp.Messaging.VerticalAnchor)parts[9].ParseToInt("CreditsController.VerticalAnchor");

                  var fadeIn = 0.5f;
                  if (parts.Length > 10)
                    fadeIn = parts[10].ParseToFloat("CreditsController.FadeIn");

                  var fadeOut = 0.5f;
                  if (parts.Length > 11)
                    fadeOut = parts[11].ParseToFloat("CreditsController.FadeOut");

                  creditsEntries.Add(
                    new TextEntry(
                      startTime,
                      length,
                      id,
                      x,
                      y,
                      parts[6],
                      alignment,
                      horizontal,
                      vertical,
                      fadeIn,
                      fadeOut
                    )
                  );
                  break;
                }
              case 2: {
                  if (parts.Length != 8) {
                    Randomizer.Warn("CreditsController", $"malformed text entry: {uncommented_line}");
                    break;
                  }

                  var startTime = parts[1].ParseToFloat("CreditsController.StartTime");
                  var length = parts[2].ParseToFloat("CreditsController.Length");
                  var id = parts[3].ParseToInt("CreditsController.ID");
                  var startX = parts[4].ParseToFloat("CreditsController.StartX");
                  var startY = parts[5].ParseToFloat("CreditsController.StartY");
                  var endX = parts[6].ParseToFloat("CreditsController.EndX");
                  var endY = parts[7].ParseToFloat("CreditsController.EndY");
                  creditsEntries.Add(
                    new MoveEntry(
                      startTime,
                      length,
                      id,
                      startX,
                      startY,
                      endX,
                      endY
                    )
                  );
                  break;
                }
              case 3: {
                  if (parts.Length < 3) {
                    Randomizer.Warn("CreditsController", $"malformed collection entry: {uncommented_line}");
                    break;
                  }

                  var id = parts[1].ParseToInt("CreditsController.ID");
                  collections[id] = parts.Skip(2).ToList();
                  break;
                }
              default:
                Randomizer.Warn("CreditsController", "Ignoring invalid type");
                break;
            }
          }
        }
      }

      creditsEntries.Sort((a, b) => (int)(a.Time - b.Time));
    }

    private static string getString(List<string> collection, int randomValue) {
      // TODO: Do more complicated logic based on value in ini file.
      return collection.ElementAt(randomValue % collection.Count);
    }

    private abstract class Entry {
      public readonly float Time;
      public readonly float Timeout;
      protected Entry(float time, float timeout) {
        Time = time;
        Timeout = timeout;
      }

      public bool ShouldResolve(float t) {
        return t >= Time;
      }

      public virtual bool Resolve(float time) {
        var finished = time >= Time + Timeout;
        if (finished)
          Reset();

        return finished;
      }

      public abstract void Reset();
    }

    private class TextEntry : Entry {
      readonly static HashSet<string> VALID_FORMATS = new HashSet<string> {
        "time",
        "int",
        "float",
        "bool"
      };

      public TextEntry(float time, float timeout, int id, float x, float y, string text,
        InterOp.Messaging.Alignment alignment, InterOp.Messaging.HorizontalAnchor horizontal,
        InterOp.Messaging.VerticalAnchor vertical, float fadeIn, float fadeOut)
        : base(time, timeout)
      {
        this.id = CreditsBaseID + id;
        this.x = x;
        this.y = y;
        this.text = text;
        this.alignment = alignment;
        this.horizontal = horizontal;
        this.vertical = vertical;
        this.fadeIn = fadeIn;
        this.fadeOut = fadeOut;

        replacements = new HashSet<int>();
        // wolf this is insane just use regexes...
        var i = 0;
        var start = 0;
        while (start != -1) {
          start = text.IndexOf("#(", i);
          if (start >= 0) {
            var end = text.IndexOf(")", start);
            if (end == -1)
              break;

            if (int.TryParse(text.Substring(start, end), out var result)) {
              replacements.Add(result);
              i = end;
            }
          }
        }
      }

      private readonly int id;
      private readonly float x;
      private readonly float y;
      private readonly string text;
      private readonly InterOp.Messaging.Alignment alignment;
      private readonly InterOp.Messaging.HorizontalAnchor horizontal;
      private readonly InterOp.Messaging.VerticalAnchor vertical;
      private readonly float fadeIn;
      private readonly float fadeOut;

      private readonly HashSet<int> replacements;
      private bool started = false;
      private int randomValue = 0;

      public string ProcessText(string text) {
        foreach (var replacement in replacements) {
          if (collections.ContainsKey(replacement))
            text = text.Replace($"#({replacement})", getString(collections[replacement], randomValue));
        }
        if (text.Contains("$(") || text.Contains("$[")) {
          return new Message(text).DisplayName;
        }
        else
          return text;
      }

      public override bool Resolve(float time) {
        if (!started) {
          randomValue = rand.Next();
          InterOp.Messaging.text_box_create(id, fadeIn, fadeOut, false, false);
          InterOp.Messaging.text_box_text(id, ProcessText(text));
          InterOp.Messaging.text_box_position(id, x, y, ZValue);
          InterOp.Messaging.text_box_alignment(id, alignment);
          InterOp.Messaging.text_box_anchor(id, horizontal, vertical);
          started = true;
        }

        return base.Resolve(time);
      }

      public override void Reset() {
        InterOp.Messaging.text_box_destroy(id);
        started = false;
      }
    }

    private class MoveEntry : Entry {
      public MoveEntry(float time, float timeout, int id, float x1, float y1, float x2, float y2) : base(time, timeout) {
        this.id = CreditsBaseID + id;
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
      }

      public readonly int id;
      public readonly float x1;
      public readonly float y1;
      public readonly float x2;
      public readonly float y2;

      private float Lerp(float a, float b, float weight) {
        return a * (1 - weight) + b * weight;
      }

      public override bool Resolve(float time) {
        var finished = base.Resolve(time);
        var weight = finished ? 1.0f : Math.Min((time - Time) / Timeout, 1.0f);
        var x = Lerp(x1, x2, weight);
        var y = Lerp(y1, y2, weight);
        InterOp.Messaging.text_box_position(id, x, y, ZValue);
        return finished;
      }

      public override void Reset() {}
    }
  }
}
