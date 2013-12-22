require "spec_helper"

describe Proceso do

  it "should return cpu core" do
     Proceso::NCPU.should_not == 0
  end

  it "should return current process" do
    Proceso.current.should_not be_nil
    Proceso.current.pid.should == Process.pid
  end

end