module CV

  class Size
    attr_accessor :width, :height

    def initialize(width = 0, height = 0)
      @width = width
      @height = height
    end

    def ==(rhs)
      @width == rhs.width && @height == rhs.height
    end

  end

  class Mat

    def size()
      return Size.new(self.cols, self.rows)
    end

  end

end
