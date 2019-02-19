from __future__ import division

import time 
import re
import sys

from PIL import Image
from io import BytesIO

import requests

from google.cloud import speech

import pyaudio 
from six.moves import queue

from azure.cognitiveservices.search.imagesearch import ImageSearchAPI
from msrest.authentication import CognitiveServicesCredentials

import asyncio

import os

# initialization
# Grab the Azure Image Search API Key
with open('bing_key.txt', 'r') as key:
	BING_KEY = key.read().strip()

# Set up the Azure client
image_client = ImageSearchAPI(CognitiveServicesCredentials(BING_KEY))

# Set up the Google Client 
# You need to export the path to the key before running the script
speech_client = speech.SpeechClient()


def search_and_display(search_string):
	image_results = image_client.images.search(query=search_string)

	if image_results.value:
		first_image_result = image_results.value[0]
		print("First image content url: {}".format(first_image_result.content_url))

		image_data = requests.get(first_image_result.thumbnail_url)

		image = Image.open(BytesIO(image_data.content))  
		print(image)
		
		# Does not work by default on raspberry pi
		# Need to install imagemagick
		image.show()


		print (image_data)


search_and_display("Lindt 90 Dark")
print("asdf")
