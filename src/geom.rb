class Point
  attr_accessor :y, :x

  def initialize(y, x)
    @y = y
    @x = x
  end

  def to_s
    "x=#{x},y=#{y}"
  end
end
