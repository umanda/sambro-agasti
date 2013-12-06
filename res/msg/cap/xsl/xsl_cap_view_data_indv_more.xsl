<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:b="urn:oasis:names:tc:emergency:cap:1.1">
<!--XSL for Short to SMS text type-->
<xsl:output method="xhtml"  omit-xml-declaration="yes" />
  
  <xsl:template match="/">
  <xsl:apply-templates/>
  </xsl:template>
  <xsl:template match="b:alert">
  
  <a>
        <xsl:attribute name="href"> 
        <xsl:text>/mod/msg/ivrtext/</xsl:text><xsl:value-of select="b:identifier"></xsl:value-of><xsl:text>.txt</xsl:text>
        <!-- <xsl:value-of select="b:identifier"></xsl:value-of>-->
        </xsl:attribute>
        <xsl:attribute name="target">
        <xsl:text>_blank</xsl:text>
        </xsl:attribute>
        <img src="res/img/cap.png"></img></a>
  
  <table class="alertView">
      <td colspan="2" class="title">Alert</td>
      <xsl:if test="b:identifier != ''">
      <tr >
      <td class="value">Identifier</td>
        <td><xsl:value-of select="b:identifier"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test="b:sender != ''">
      <tr >
      <td class="value">Sender</td>
        <td><xsl:value-of select="b:sender"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:sent != ''">
      <tr >
      <td class="value">Sent</td>
        <td><xsl:value-of select="b:sent"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:status != ''">
      <tr >
      <td class="value">Status</td>
        <td><xsl:value-of select="b:status"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "msgType != ''">
      <tr >
      <td class="value">Message Type</td>
        <td><xsl:value-of select="b:msgType"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test="b:source != ''">
      <tr >
      <td class="value">Source</td>
        <td><xsl:value-of select="b:source"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:scope != ''">
      <tr >
      <td class="value">Scope</td>
        <td><xsl:value-of select="b:scope"></xsl:value-of></td>
      </tr>
      <xsl:if test = "b:restriction != ''">
      <tr >
      <td class="value">Restriction</td>
        <td><xsl:value-of select="b:restriction"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:address != ''">
      <tr >
      <td class="value">Address</td>
        <td><xsl:value-of select="b:address"></xsl:value-of></td>
      </tr>
      </xsl:if>
      </xsl:if>
      <xsl:if test = "b:code != ''">
      <tr >
      <td class="value">Code</td>
        <td><xsl:value-of select="b:code"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:references != ''">
       <tr >
      <td class="value">References</td>
        <td><xsl:value-of select="b:references"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:incidents != ''">
      <tr >
      <td class="value">Incidents</td>
        <td><xsl:value-of select="b:incidents"></xsl:value-of></td>
      </tr>
      </xsl:if>
      </table>
      <table class="alertView">
      <td colspan="2" class="title">Info</td>
      <xsl:if test = "b:info/b:language != ''">
      <tr >
      <td class="value">Language</td>
        <td><xsl:value-of select="b:info/b:language"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test="b:info/b:category != ''">
      <tr >
      <td class="value">Category</td>
        <td><xsl:value-of select="b:info/b:category"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:event != ''">
      <tr >
      <td class="value">Event</td>
        <td><xsl:value-of select="b:info/b:event"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:responseType != ''">
      <tr >
      <td class="value">Response Type</td>
        <td><xsl:value-of select="b:info/b:responseType"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:priority != ''">
      <tr >
      <td class="value">Priority</td>
        <td><xsl:value-of select="b:info/b:priority"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:urgency != ''">
      <tr >
      <td class="value">Urgency</td>
        <td><xsl:value-of select="b:info/b:urgency"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:severity != ''">
      <tr >
      <td class="value">Severity</td>
        <td><xsl:value-of select="b:info/b:severity"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:certainty != ''">
      <tr >
      <td class="value">Certainty</td>
        <td><xsl:value-of select="b:info/b:certainty"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:audience != ''">
      <tr >
      <td class="value">Audience</td>
        <td><xsl:value-of select="b:info/b:audience"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:effective != ''">
      <tr >
      <td class="value">Effective</td>
        <td><xsl:value-of select="b:info/b:effective"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:onset != ''">
      <tr >
      <td class="value">onset</td>
        <td><xsl:value-of select="b:info/b:onset"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:expires != ''">
      <tr >
      <td class="value">Expires</td>
        <td><xsl:value-of select="b:info/b:expires"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:senderName != ''">
      <tr >
      <td class="value">Sender Name</td>
        <td><xsl:value-of select="b:info/b:senderName"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:headline != ''">
      <tr >
      <td class="value">Headline</td>
        <td><xsl:value-of select="b:info/b:headline"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:description != ''">
      <tr >
      <td class="value">Description</td>
        <td><xsl:value-of select="b:info/b:description"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:instruction != ''">
      <tr >
      <td class="value">Instruction</td>
        <td><xsl:value-of select="b:info/b:instruction"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:web != ''">
      <tr >
      <td class="value">Web</td>
        <td>
        <a><xsl:attribute name="href"> 
        <xsl:text>http://</xsl:text>
        <xsl:value-of select="b:info/b:web"></xsl:value-of>
        </xsl:attribute>
        <xsl:value-of select="b:info/b:web"></xsl:value-of></a></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:contact != ''">
      <tr >
      <td class="value">Contact</td>
        <td><xsl:value-of select="b:info/b:contact"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:eventCode/b:valueName != ''">
      <tr >
      <td class="value">Event Code</td>
        <td><b>Value Name : </b><xsl:value-of select="b:info/b:eventCode/b:valueName"></xsl:value-of> 
        <br></br><b>Value : </b> <xsl:value-of select="b:info/b:eventCode/b:value"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:parameter/b:valueName != ''">
      <tr >
      <td class="value">Parameter</td>
        <td><b>Value Name : </b><xsl:value-of select="b:info/b:parameter/b:valueName"></xsl:value-of> 
        <br></br><b>Value : </b> <xsl:value-of select="b:info/b:parameter/b:value"></xsl:value-of></td>
      </tr>
      </xsl:if>
      </table>
      <table class="alertView">
      <td colspan="2" class="title">Resource</td>
      <xsl:if test = "b:info/b:resource/b:resourceDesc != ''">
      <tr >
      <td class="value">Resource Description</td>
        <td><xsl:value-of select="b:info/b:resource/b:resourceDesc"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:resource/b:mimeType != ''">
      <tr >
      <td class="value">MIME Type</td>
        <td><xsl:value-of select="b:info/b:resource/b:mimeType"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:resource/b:size != ''">
      <tr >
      <td class="value">Size</td>
        <td><xsl:value-of select="b:info/b:resource/b:size"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:resource/b:uri != ''">
      <tr >
      <td class="value">URI</td>
        <td><xsl:value-of select="b:info/b:resource/b:uri"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:resource/b:digest != ''">
      <tr >
      <td class="value">Digest</td>
        <td><xsl:value-of select="b:info/b:resource/b:digest"></xsl:value-of></td>
      </tr>
      </xsl:if>
      </table>
      <table class="alertView">
      <td colspan="2" class="title">Area</td>
      <xsl:if test = "b:info/b:area/b:areaDesc != ''">
      <tr >
      <td class="value">Area Description</td>
        <td><xsl:value-of select="b:info/b:area/b:areaDesc"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:area/b:locationCategory != ''">
      <tr >
      <td class="value">Location Category</td>
        <td><xsl:value-of select="b:info/b:area/b:locationCategory"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:area/b:locationType != ''">
      <tr >
      <td class="value">Location Type</td>
        <td><xsl:value-of select="b:info/b:area/b:locationType"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:area/b:polygon != ''">
      <tr >
      <td class="value">Polygon</td>
        <td><xsl:value-of select="b:info/b:area/b:polygon"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:area/b:circle != ''">
      <tr >
      <td class="value">Circle</td>
        <td><xsl:value-of select="b:info/b:area/b:circle"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:info/b:area/b:geocode/b:valueName != ''">
      <tr >
      <td class="value">Geo Code</td>
        <td><b>Value Name : </b><xsl:value-of select="b:info/b:area/b:geocode/b:valueName"></xsl:value-of>
        <br></br>
        <b>Value : </b><xsl:value-of select="b:info/b:area/b:geocode/b:value"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test="b:info/b:area/b:altitude != ''"> 
      <tr >
      <td class="value">Altitude</td>
        <td><xsl:value-of select="b:info/b:area/b:altitude"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test="b:info/b:area/b:ceiling != ''">
      <tr >
      <td class="value">Ceiling</td>
        <td><xsl:value-of select="b:info/b:area/b:ceiling"></xsl:value-of></td>
      </tr>
      </xsl:if>
      </table>
  </xsl:template>
</xsl:stylesheet>

