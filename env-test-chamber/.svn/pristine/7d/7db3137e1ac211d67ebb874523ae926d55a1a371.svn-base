#!/usr/bin/python
import smtplib
sender = 'etc@colorado.edu'
receivers = ['koenigp@colorado.edu']
message = """From: Paul Koenig <koenigp@colorado.edu> 
To: Paul Koenig<koenigp@colorado.edu>
Subject: email Test

test
test
"""
smtpObj = smtplib.SMTP('localhost')
smtpObj.sendmail(sender,receivers, message)
print "Success"
