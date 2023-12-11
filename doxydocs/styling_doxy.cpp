//Module for custom objects.

/**
 * @addtogroup stylingModule
 * @{
 * @details
 *
 * \section stylingModule Styling
 *
 * Styling refers to the overall design for the Graphical User Interface. Styling includes color of centein objects and pages, the font and sizes for text and titles, and even the positioning and sizes of objects on pages. Styling is significantly important not only to the NVENT-VITA, but to UI Development in general, for it is important to the visual appeal, improving user experience, reinforcing branding and identity, differentiation to other products, and aiding in the communication between user and interface.
 *
 * The Font Family chosen for the display: <b>Roboto</b>.<br>
 *
 * Roboto was chosen for the font family for all texts on the Graphical User Interface for its readability and its modern aesthetic that makes it a suitable choice for contemporary designs. The font family also makes the NVENT-Vita look more professional, especially in the field of medicine. Style variations for the font family include: Black, Black Italic, Bold, Bold Italic, Italic, Light, Light Italic, Medium, Medium Italic, Regular, Thin, and Thin Italic.
 *
 * Text on the GUI will be displayed in different style variations of the Roboto Font Family, and sizes. Text and object will be displayed in different sizes, and colors. <br><br>
 *
 * For the Hex Code representing colors (some color are meant to be transparent and utilized as a alpha layer):
 *
 * <table>
 *  <tr>
 *      <th>Color Name</th>
 *      <th>Hex Code</th>
 *  </tr>
 *  <tr>
 *      <th>Primary</th>
 *      <td>@htmlonly <font color="#3D96A8">#3D96A8</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Secondary</th>
 *      <td>@htmlonly <font color="#6FCC68">#6FCC68</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Tertiary</th>
 *      <td>@htmlonly <font color="#FAE061">#FAE061</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>\htmlonly PIP\endhtmlonly</th>
 *      <td>@htmlonly <font color="#C12E30">#C12E30</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>SP</th>
 *      <td>@htmlonly <font color="#0E6CBF">#0E6CBF</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Primary Dark</th>
 *      <td>@htmlonly <font color="#202531">#202531</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Primary Light</th>
 *      <td>@htmlonly <font color="#E3ECFB">#E3ECFB</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Primary Dark Translucent</th>
 *      <td>@htmlonly <font color="#8C202531">#8C202531</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>General Measured Value</th>
 *      <td>@htmlonly <font color="#E6E3ECFB">#E6E3ECFB</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>General Set Display</th>
 *      <td>@htmlonly <font color="#4A90E2">#4A90E2</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Scale Rectangle Border</th>
 *      <td>@htmlonly <font color="#66F2F2F2">#66F2F2F2</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Unit</th>
 *      <td>@htmlonly <font color="#99E3ECFB">#99E3ECFB</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Min and Max</th>
 *      <td>@htmlonly <font color="#BFE3ECFB">#BFE3ECFB</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Transparent</th>
 *      <td>@htmlonly <font color="#00000000">#00000000</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Unclickable Border</th>
 *      <td>@htmlonly <font color="#313C51">#313C51</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Statistic Value</th>
 *      <td>@htmlonly <font color="#E6E3ECFB">#E6E3ECFB</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Mode Active</th>
 *      <td>@htmlonly <font color="#1F2A34">#1F2A34</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Mode Inactive</th>
 *      <td>@htmlonly <font color="#506385">#506385</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Mode Label</th>
 *      <td>@htmlonly <font color="#3D96A8">#3D96A8</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Primary Light Selected</th>
 *      <td>@htmlonly <font color="#1AE3ECFB">#1AE3ECFB</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Numeric UI Unit</th>
 *      <td>@htmlonly <font color="#A1A7B2">#A1A7B2</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Affirmative</th>
 *      <td>@htmlonly <font color="#4AE287">#4AE287</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Affirmative Translucent</th>
 *      <td>@htmlonly <font color="#804AE287">#804AE287</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Dissident</th>
 *      <td>@htmlonly <font color="#FF223D">#FF223D</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Cancel</th>
 *      <td>@htmlonly <font color="#E24A5F">#E24A5F</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Primary Light Disabled</th>
 *      <td>@htmlonly <font color="#8CE3ECFB">#8CE3ECFB</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Patient \htmlonly Warning\endhtmlonly</th>
 *      <td>@htmlonly <font color="#F24C26">#F24C26</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>System \htmlonly Warning\endhtmlonly</th>
 *      <td>@htmlonly <font color="#4A5AE4">#4A5AE4</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>\htmlonly Notice\endhtmlonly</th>
 *      <td>@htmlonly <font color="#E2C044">#E2C044</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>\htmlonly Warning \endhtmlonly Description</th>
 *      <td>@htmlonly <font color="#8CE3ECFB">#8CE3ECFB</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Menu Color</th>
 *      <td>@htmlonly <font color="#313C51">#313C51</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Mode Active \htmlonly Warning\endhtmlonly</th>
 *      <td>@htmlonly <font color="#FBA455">#FBA455</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>O<sub>2</sub> Color</th>
 *      <td>@htmlonly <font color="#6FCC68">#6FCC68</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Help Icon Selected</th>
 *      <td>@htmlonly <font color="#804A90E2">#804A90E2</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>Mode Active \htmlonly Warning \endhtmlonly Selected</th>
 *      <td>@htmlonly <font color="#8CFBA455">#8CFBA455</font> @endhtmlonly</td>
 *  </tr>
 *  <tr>
 *      <th>General Set Display Selected</th>
 *      <td>@htmlonly <font color="#8C4A90E2">#8C4A90E2</font> @endhtmlonly</td>
 *  </tr>
 * </table><br>
 *
 * Font Styles built from the Roboto Font Family, Style Variations, Sizes, and Weights:<br>
 *
 * <table>
 *  <tr>
 *      <th>Font</th>
 *  </tr>
 *  <tr><td style="font-family: 'Roboto Black', sans-serif; font-weight: 900; font-size: 96px; word-wrap: break-word;"><br><br>Measured Font <br><br><br></tr>
 *  <tr><td style="font-family: 'Roboto Black', sans-serif; font-weight: 900; font-size: 72px; word-wrap: break-word;"><br><br>Loading Text Font <br><br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Bold', sans-serif; font-size: 36px; word-wrap: break-word;"><br><br>Page Title Font <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Black', sans-serif; font-size: 34px; word-wrap: break-word;"><br><br>Statistic Font <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Bold', sans-serif; font-size: 32px; word-wrap: break-word;"><br><br>Set Font <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Medium', sans-serif; font-size: 32px; word-wrap: break-word;"><br><br> Numeric UI Display Font <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Black', sans-serif; font-size: 30px; word-wrap: break-word;"><br><br> Statistic Font (Small Version) <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Black', sans-serif; font-size: 24px; word-wrap: break-word;"><br>\htmlonly Warning \endhtmlonly Flag Font <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Medium', sans-serif; font-size: 24px; word-wrap: break-word;"><br>\htmlonly Warning \endhtmlonly  Title Font <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Medium', sans-serif; font-size: 24px; word-wrap: break-word;"><br>Number Button Font <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Bold', sans-serif; font-size: 24px; word-wrap: break-word;"><br>Setting Page Title <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Bold', sans-serif; font-size: 18px; word-wrap: break-word;"><br>Title Font <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Bold', sans-serif; font-size: 18px; word-wrap: break-word;"><br>Unit Font <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Bold', sans-serif; font-size: 18px; word-wrap: break-word;"><br>Min and Max Font <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Medium', sans-serif; font-size: 18px; word-wrap: break-word;"><br><u>Cancel Font <br><br></u></td></tr>
 *  <tr><td style="font-family: 'Roboto Bold', sans-serif; font-size: 18px; word-wrap: break-word;"><br>\htmlonly Warning \endhtmlonly  Description Font <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Medium', sans-serif; font-size: 17px; word-wrap: break-word;"><br>Button Font <br><br></td></tr>
 *  <tr><td style="font-family: 'Roboto Medium', sans-serif; font-size: 17px; word-wrap: break-word;"><br><u>Button Font Underlined <br><br></u></td></tr>
 *  <tr><td style="font-family: 'Roboto Medium', sans-serif; font-size: 12px; word-wrap: break-word;"><br>Small Button Font <br><br></td></tr>
 * </table><br><br>
 *
 * Contant texts used on the GUI for the Pneumatic Setting Titles and Units.
 * Constants included:
 * - \htmlonly PIP \endhtmlonly Title: Peak Insp. Pressure
 * - SP Title: Stacking Pressure
 * - Auxiliary Flow Title: Auxiliary
 * - \htmlonly Humidity \endhtmlonly Title: \htmlonly Humidity \endhtmlonly
 * - Driving Pressure Title: Driving Pressure
 * - \htmlonly Rate \endhtmlonly Title: \htmlonly Rate \endhtmlonly
 * - Inspiratory Time Title: Inspiratory Time
 * - Oxygen Title: Oxygen
 * - cmH<sub>2</sub>O Unit: cmH<sub>2</sub>
 * - LPM Unit: lpm
 * - Percent Unit: %
 * - PSI Unit: PSI
 * - BPM Unit: BPM
 * - ml Unit: ml
 * - MAP Unit: MAP
 * - TV Unit: TV
 * - MV Unit: MV
 *
 * @file Roboto-Black.ttf
 * @file Roboto-BlackItalic.ttf
 * @file Roboto-Bold.ttf
 * @file Roboto-BoldItalic.ttf
 * @file Roboto-Italic.ttf
 * @file Roboto-Light.ttf
 * @file Roboto-LightItalic.ttf
 * @file Roboto-Medium.ttf
 * @file Roboto-MediumItalic.ttf
 * @file Roboto-Regular.ttf
 * @file Roboto-Thin.ttf
 * @file Roboto-ThinItalic.ttf
 *
 * @file Style.qml
 * @brief File containing fonts and colors.
 *
 * @file Strings.qml
 * @brief String constants for titles and units.
 *
 *
                                 Apache License
                           Version 2.0, January 2004
                        http://www.apache.org/licenses/

   TERMS AND CONDITIONS FOR USE, REPRODUCTION, AND DISTRIBUTION

   1. Definitions.

      "License" shall mean the terms and conditions for use, reproduction,
      and distribution as defined by Sections 1 through 9 of this document.

      "Licensor" shall mean the copyright owner or entity authorized by
      the copyright owner that is granting the License.

      "Legal Entity" shall mean the union of the acting entity and all
      other entities that control, are controlled by, or are under common
      control with that entity. For the purposes of this definition,
      "control" means (i) the power, direct or indirect, to cause the
      direction or management of such entity, whether by contract or
      otherwise, or (ii) ownership of fifty percent (50%) or more of the
      outstanding shares, or (iii) beneficial ownership of such entity.

      "You" (or "Your") shall mean an individual or Legal Entity
      exercising permissions granted by this License.

      "Source" form shall mean the preferred form for making modifications,
      including but not limited to software source code, documentation
      source, and configuration files.

      "Object" form shall mean any form resulting from mechanical
      transformation or translation of a Source form, including but
      not limited to compiled object code, generated documentation,
      and conversions to other media types.

      "Work" shall mean the work of authorship, whether in Source or
      Object form, made available under the License, as indicated by a
      copyright notice that is included in or attached to the work
      (an example is provided in the Appendix below).

      "Derivative Works" shall mean any work, whether in Source or Object
      form, that is based on (or derived from) the Work and for which the
      editorial revisions, annotations, elaborations, or other modifications
      represent, as a whole, an original work of authorship. For the purposes
      of this License, Derivative Works shall not include works that remain
      separable from, or merely link (or bind by name) to the interfaces of,
      the Work and Derivative Works thereof.

      "Contribution" shall mean any work of authorship, including
      the original version of the Work and any modifications or additions
      to that Work or Derivative Works thereof, that is intentionally
      submitted to Licensor for inclusion in the Work by the copyright owner
      or by an individual or Legal Entity authorized to submit on behalf of
      the copyright owner. For the purposes of this definition, "submitted"
      means any form of electronic, verbal, or written communication sent
      to the Licensor or its representatives, including but not limited to
      communication on electronic mailing lists, source code control systems,
      and issue tracking systems that are managed by, or on behalf of, the
      Licensor for the purpose of discussing and improving the Work, but
      excluding communication that is conspicuously marked or otherwise
      designated in writing by the copyright owner as "Not a Contribution."

      "Contributor" shall mean Licensor and any individual or Legal Entity
      on behalf of whom a Contribution has been received by Licensor and
      subsequently incorporated within the Work.

   2. Grant of Copyright License. Subject to the terms and conditions of
      this License, each Contributor hereby grants to You a perpetual,
      worldwide, non-exclusive, no-charge, royalty-free, irrevocable
      copyright license to reproduce, prepare Derivative Works of,
      publicly display, publicly perform, sublicense, and distribute the
      Work and such Derivative Works in Source or Object form.

   3. Grant of Patent License. Subject to the terms and conditions of
      this License, each Contributor hereby grants to You a perpetual,
      worldwide, non-exclusive, no-charge, royalty-free, irrevocable
      (except as stated in this section) patent license to make, have made,
      use, offer to sell, sell, import, and otherwise transfer the Work,
      where such license applies only to those patent claims licensable
      by such Contributor that are necessarily infringed by their
      Contribution(s) alone or by combination of their Contribution(s)
      with the Work to which such Contribution(s) was submitted. If You
      institute patent litigation against any entity (including a
      cross-claim or counterclaim in a lawsuit) alleging that the Work
      or a Contribution incorporated within the Work constitutes direct
      or contributory patent infringement, then any patent licenses
      granted to You under this License for that Work shall terminate
      as of the date such litigation is filed.

   4. Redistribution. You may reproduce and distribute copies of the
      Work or Derivative Works thereof in any medium, with or without
      modifications, and in Source or Object form, provided that You
      meet the following conditions:

      (a) You must give any other recipients of the Work or
          Derivative Works a copy of this License; and

      (b) You must cause any modified files to carry prominent notices
          stating that You changed the files; and

      (c) You must retain, in the Source form of any Derivative Works
          that You distribute, all copyright, patent, trademark, and
          attribution notices from the Source form of the Work,
          excluding those notices that do not pertain to any part of
          the Derivative Works; and

      (d) If the Work includes a "NOTICE" text file as part of its
          distribution, then any Derivative Works that You distribute must
          include a readable copy of the attribution notices contained
          within such NOTICE file, excluding those notices that do not
          pertain to any part of the Derivative Works, in at least one
          of the following places: within a NOTICE text file distributed
          as part of the Derivative Works; within the Source form or
          documentation, if provided along with the Derivative Works; or,
          within a display generated by the Derivative Works, if and
          wherever such third-party notices normally appear. The contents
          of the NOTICE file are for informational purposes only and
          do not modify the License. You may add Your own attribution
          notices within Derivative Works that You distribute, alongside
          or as an addendum to the NOTICE text from the Work, provided
          that such additional attribution notices cannot be construed
          as modifying the License.

      You may add Your own copyright statement to Your modifications and
      may provide additional or different license terms and conditions
      for use, reproduction, or distribution of Your modifications, or
      for any such Derivative Works as a whole, provided Your use,
      reproduction, and distribution of the Work otherwise complies with
      the conditions stated in this License.

   5. Submission of Contributions. Unless You explicitly state otherwise,
      any Contribution intentionally submitted for inclusion in the Work
      by You to the Licensor shall be under the terms and conditions of
      this License, without any additional terms or conditions.
      Notwithstanding the above, nothing herein shall supersede or modify
      the terms of any separate license agreement you may have executed
      with Licensor regarding such Contributions.

   6. Trademarks. This License does not grant permission to use the trade
      names, trademarks, service marks, or product names of the Licensor,
      except as required for reasonable and customary use in describing the
      origin of the Work and reproducing the content of the NOTICE file.

   7. Disclaimer of Warranty. Unless required by applicable law or
      agreed to in writing, Licensor provides the Work (and each
      Contributor provides its Contributions) on an "AS IS" BASIS,
      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
      implied, including, without limitation, any warranties or conditions
      of TITLE, NON-INFRINGEMENT, MERCHANTABILITY, or FITNESS FOR A
      PARTICULAR PURPOSE. You are solely responsible for determining the
      appropriateness of using or redistributing the Work and assume any
      risks associated with Your exercise of permissions under this License.

   8. Limitation of Liability. In no event and under no legal theory,
      whether in tort (including negligence), contract, or otherwise,
      unless required by applicable law (such as deliberate and grossly
      negligent acts) or agreed to in writing, shall any Contributor be
      liable to You for damages, including any direct, indirect, special,
      incidental, or consequential damages of any character arising as a
      result of this License or out of the use or inability to use the
      Work (including but not limited to damages for loss of goodwill,
      work stoppage, computer failure or malfunction, or any and all
      other commercial damages or losses), even if such Contributor
      has been advised of the possibility of such damages.

   9. Accepting Warranty or Additional Liability. While redistributing
      the Work or Derivative Works thereof, You may choose to offer,
      and charge a fee for, acceptance of support, warranty, indemnity,
      or other liability obligations and/or rights consistent with this
      License. However, in accepting such obligations, You may act only
      on Your own behalf and on Your sole responsibility, not on behalf
      of any other Contributor, and only if You agree to indemnify,
      defend, and hold each Contributor harmless for any liability
      incurred by, or claims asserted against, such Contributor by reason
      of your accepting any such warranty or additional liability.

   END OF TERMS AND CONDITIONS

   APPENDIX: How to apply the Apache License to your work.

      To apply the Apache License to your work, attach the following
      boilerplate notice, with the fields enclosed by brackets "[]"
      replaced with your own identifying information. (Don't include
      the brackets!)  The text should be enclosed in the appropriate
      comment syntax for the file format. We also recommend that a
      file or class name and description of purpose be included on the
      same "printed page" as the copyright notice for easier
      identification within third-party archives.

   Copyright [yyyy] [name of copyright owner]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 * @}
 */
