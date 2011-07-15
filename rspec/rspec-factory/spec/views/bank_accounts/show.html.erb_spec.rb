require 'spec_helper'

describe "bank_accounts/show.html.erb" do
  before(:each) do
    @bank_account = assign(:bank_account, stub_model(BankAccount))
  end

  it "renders attributes in <p>" do
    render
  end
end
