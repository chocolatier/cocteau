from __future__ import division

import time 
import re
import sys

from google.cloud import speech

import pyaudio 
from six.moves import queue

from azure.cognitiveservices.search.imagesearch import ImageSearchAPI
from msrest.authentication import CognitiveServicesCredentials

import asyncio

# initialization
# Grab the Azure Image Search API Key
with open('bing_key.txt', 'r') as key:
	BING_KEY = key.read().strip()

image_client = ImageSearchAPI(CognitiveServicesCredentials(BING_KEY))
speech_client = speech.SpeechClient()


def search_and_display(search_string):
	image_results = image_client.images.search(query=search_string)

	if image_results.value:
		first_image_result = image_results.value[0]
		print("First image content url: {}".format(first_image_result.content_url))


# init()
search_and_display("Lindt 90 Dark")
print("asdf")
