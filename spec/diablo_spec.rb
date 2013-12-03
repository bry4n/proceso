require "spec_helper"

describe Diablo do

  it "should create new Base object with argument" do
    expect { Diablo::Base.new(1) }.to_not raise_error
  end

  it "creates new Base object without argument will raise error" do
    expect { Diablo::Base.new }.to raise_error
  end

end