class AccountsController < ApplicationController
  def show
    @accounts = Account.all
    
    respond_to do |format|
      format.html # show.html.erb
      format.json { render :json => @accounts }
    end
  end
end
