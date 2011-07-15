#!/usr/bin/env ruby
%w[rubygems csv time riak].each{|lib| require lib}

#client  = Riak::Client.new # or: Riak::Client.new(:port => 8097)
client = Riak::Client.new(:host => "172.27.12.133", :http_port => 8098)
bucket  = client['goog']

quotes  = CSV.read 'goog.csv'
header  = quotes.shift

quotes.each do |row|
  obj = bucket.new row.first

  puts obj.key

  obj.data = Hash[ [header, row].transpose ]
  obj.store
end
