<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:b="urn:oasis:names:tc:emergency:cap:1.1">
<!--XSL for Short to SMS text type-->
<xsl:output method="xhtml" omit-xml-declaration="yes"/>
  
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
  <xsl:if test = "b:info/b:priority != ''">
      <tr >
      <td class="value">Priority</td>
        <xsl:element name="td">
            <xsl:attribute name="class"><xsl:value-of select="b:info/b:priority"/></xsl:attribute>
                <span><xsl:value-of select="b:info/b:priority"/></span>
        </xsl:element>
      </tr>
      </xsl:if>
      <xsl:if test="b:msgType != ''">
      <tr >
      <td class="value">Message Type</td>
        <td><xsl:value-of select="b:msgType"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test="b:info/b:senderName != ''">
      <tr >
      <td class="value">Sender</td>
        <td><xsl:value-of select="b:info/b:senderName"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test="b:sent != ''">
      <tr >
      <td class="value">Sent</td>
        <td><xsl:value-of select="b:sent"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test="b:info/b:event != ''">
       <tr >
      <td class="value">Event</td>
        <td><xsl:value-of select="b:info/b:event"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test = "b:status != ''">
      <tr >
      <td class="value">Status</td>
        <td><xsl:value-of select="b:status"></xsl:value-of></td>
      </tr>
      </xsl:if>
      
       <xsl:if test = "b:info/b:category != ''">
      <tr >
      <td class="value">Category</td>
        <td><xsl:value-of select="b:info/b:category"></xsl:value-of></td>
      </tr>
      </xsl:if>
       <xsl:if test = "b:msgType != ''">
      <tr >
      <td class="value">Message Type</td>
        <td><xsl:value-of select="b:msgType"></xsl:value-of></td>
      </tr>
      </xsl:if>
      
      <xsl:if test="b:code != ''">
      <tr >
      <td class="value">Code</td>
        <td><xsl:value-of select="b:code"></xsl:value-of></td>
      </tr>
      </xsl:if>
      <xsl:if test="b:info/b:web != ''">
      <tr >
      <td class="value">Web</td>
        <td><a>
        <xsl:attribute name="href"> 
        <xsl:text>http://</xsl:text>
        <xsl:value-of select="b:info/b:web"></xsl:value-of>
        </xsl:attribute>
        <xsl:value-of select="b:info/b:web"></xsl:value-of></a></td>
      </tr>      
      </xsl:if>
      </table>
        <br />
  </xsl:template>
</xsl:stylesheet>

