<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:b="urn:oasis:names:tc:emergency:cap:1.1"
xmlns:php="http://php.net/xsl">
<!--XSL for Short to SMS text type-->
<xsl:output method="html" omit-xml-declaration="yes" />
  
  <xsl:template match="/">
  <xsl:apply-templates/>
  </xsl:template>
  <xsl:template match="b:alert">
  
      <tr>
        <td>
            <a><xsl:attribute name="href"><xsl:text></xsl:text>
            <xsl:text>index.php?mod=msg&amp;act=view_list_alert&amp;seq=indv_alert&amp;identifier=</xsl:text>
            <xsl:value-of select="b:identifier"></xsl:value-of>
            </xsl:attribute>
            <xsl:choose>
            <xsl:when test="b:info/b:headline != ''">
            <xsl:value-of select="b:info/b:headline"></xsl:value-of>
            </xsl:when>
            <xsl:otherwise>
            <xsl:value-of select="php:function('shn_msg_default_title')"></xsl:value-of>
            <!-- <xsl:text>Default Title</xsl:text>-->
            </xsl:otherwise>
            </xsl:choose>       
            
            <xsl:choose>
            <xsl:when test="b:info/b:area/b:areaDesc != ''">
            <xsl:text>, </xsl:text>
            <xsl:value-of select="b:info/b:area/b:areaDesc"></xsl:value-of>
            </xsl:when>
            <!--<xsl:otherwise>
            <xsl:text>Default Area</xsl:text>
            </xsl:otherwise>-->
            </xsl:choose>
             <br></br>             
            </a><xsl:value-of select="b:sent"></xsl:value-of>
            <br></br>
             <xsl:choose>
             <xsl:when test="b:info/b:category != ''">
             <xsl:text> Category of </xsl:text>
             <b><xsl:value-of select="b:info/b:category"></xsl:value-of></b>
             <xsl:if test="b:msgType != ''"> 
             <xsl:text> and </xsl:text>
             </xsl:if>
             </xsl:when>
             </xsl:choose>
             
             <xsl:choose>
             <xsl:when test="b:msgType != ''">
              <xsl:text> Message Type of </xsl:text>
             <b><xsl:value-of select="b:msgType"></xsl:value-of></b>
             </xsl:when>
             </xsl:choose>
             </td>
             

    <xsl:element name="td">
        <xsl:attribute name="class"><xsl:value-of select="b:info/b:priority"/></xsl:attribute>
            <span><xsl:value-of select="b:info/b:priority"/></span>
    </xsl:element>
        <td> By </td>
        <td>
       	<xsl:choose>
       	<xsl:when test="b:info/b:senderName != ''">
       	<xsl:value-of select="b:info/b:senderName"/>
       	</xsl:when>
       	<xsl:otherwise>
       	<xsl:text>Unknown Sender</xsl:text>
       	</xsl:otherwise>
       	</xsl:choose>
        </td>
        <!-- <td>Sender Name</td>
        <td><xsl:value-of select="b:info/b:senderName"/></td>-->
      </tr>
  </xsl:template>
</xsl:stylesheet>

