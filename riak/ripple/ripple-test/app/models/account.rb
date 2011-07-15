
# For Riak Database
class Account 
  include Ripple::Document
	
  property :name, String, :presence => true
  property :email, String
  property :phone, String
  property :address, String
  property :type, Integer, :presence => true
  property :active, Boolean, :default => true, :presence => true
  
  # Let's add the timestamps. We like this for everything!
  timestamps!

  #many :units
  #many :users

  # Parent accounts are stored as links in Riak. Later we can create a script
  # to change this a little bit for SQL databases if needed.\
  # Also, we need to create links for each and every unit that belongs 
  # to this account.
end

# For SQL database
#class Account < ActiveRecord::Base
#end
