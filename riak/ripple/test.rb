require 'ripple'

class Email
  include Ripple::Document
  property :from, String, :presence => true
  property :to,   String, :presence => true
  property :sent, Time,   :default => proc { Time.now }
  property :body, String
end

email = Email.new
email.from = "xtremekforever@gmail.com"
email.to = "godsgirl411@gmail.com"
email.body = "I wonder why some people are afraid of the friend zone..."
email.save

class Person
  include Ripple::Document
  property :name, String
  many :addresses
  many :friends, :class_name => "Person"
  one :account
end

class Account
  include Ripple::EmbeddedDocument
  property :paid_until, Time
  embedded_in :person
end

class Address
  include Ripple::EmbeddedDocument
  property :street, String
  property :city,   String
  property :state,  String
  property :zip,    String
end

person = Person.new(:name => "jzamora")
person.account.paid_until = 3.months.from_now
person.save
