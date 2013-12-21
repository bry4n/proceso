require "spec_helper"

describe Proceso do

  it "should return cpu core" do
     Proceso::NCPU.should_not == 0
  end

end