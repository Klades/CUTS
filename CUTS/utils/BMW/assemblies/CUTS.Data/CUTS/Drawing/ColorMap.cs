// -*- C# -*-

using System;
using System.Collections;
using System.Drawing;

namespace CUTS.Drawing
{
  public class ColorMap
  {
    public ColorMap ()
    {
      this.diameter_ = this.random_.Next (0, 255);
      this.radius_ = this.diameter_ / 2;
    }

    public ColorMap (int diameter)
    {
      this.diameter_ = diameter;
      this.radius_ = this.diameter_ / 2;
    }

    public Color Add (object key)
    {
      // First, validate the key does not already exist.
      if (this.map_.ContainsKey (key))
        return (Color)this.map_[key];

      // Generate a new color for the key.
      Color color = this.generate_random_color ();
      this.map_.Add (key, color);

      return color;
    }

    public Color Add (object key, Color color)
    {
      if (this.map_.ContainsKey (key))
      {
        this.map_[key] = color;
      }
      else if (this.map_.ContainsValue (color))
      {
        color = this.generate_random_color ();
        this.map_.Add (key, color);
      }
      else
      {
        this.map_.Add (key, color);
      }

      return color;
    }

    public void Clear ()
    {
      this.map_.Clear ();
    }

    public int Count
    {
      get
      {
        return this.map_.Count;
      }
    }

    private Color generate_random_color ()
    {
      Color color;

      do
      {
        // Generate a random position along the gray diagonal.
        int r = this.random_.Next (0, 255), g = r, b = r;

        // Perturb the colors by a small random amount.
        r += ((this.random_.Next () % this.diameter_) - this.radius_);
        g += ((this.random_.Next () % this.diameter_) - this.radius_);
        b += ((this.random_.Next () % this.diameter_) - this.radius_);

        // Clip the resulting R,G,B back to byte values.
        if (r < 0)
          r = 0;
        else if (r > 255)
          r = 255;

        if (g < 0)
          g = 0;
        else if (g > 255)
          g = 255;

        if (b < 0)
          b = 0;
        else if (b > 255)
          b = 255;

        color = Color.FromArgb (r, g, b);
      } while (this.map_.ContainsValue (color));

      return color;
    }

    private Hashtable map_ = new Hashtable ();

    private Random random_ =
      new Random (unchecked ((int)DateTime.Now.Ticks));

    private int diameter_;

    private int radius_;
  }
}
