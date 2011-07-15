require 'riak'

puts "Welcome to the XK Riak Test app!"
puts "First let's connect to the cluster..."
client = Riak::Client.new(:host => "172.27.12.133", :http_port => 8098)
puts "Ok great, so now we must get the bucket \"test\"..."
bucket = client.bucket("test")

puts "This time we're going to see what we can find in \"index.html\" in our"
puts "bucket. Here goes!"

object = bucket.get("index.html")

puts "So we got it! Let's see what's in it: "
puts object.data


#puts "So far so good. Now, lets create \"index.html\" in that bucket"
#puts "to see what happens!"
#object = Riak::RObject.new(bucket, "index.html")
#object.content_type = "text/html"
#object.data = "<html><body>Hello, Riak on Rails!</body></html>"
#object.store

#puts "We just put this data in the object: "
#puts object.data
