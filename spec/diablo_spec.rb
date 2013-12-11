require "spec_helper"

describe Diablo do

  it "should create new Process object with pid" do
    expect { Diablo::Process.new($$) }.to_not raise_error
  end

  it "creates new Base object without argument will raise error" do
    expect { Diablo::Process.new }.to raise_error
  end

  it "should return process name" do
    process = Diablo::Process.new($$)
    process.name.should =~ /ruby/
  end

end